#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void airports(char * fname){
    FILE * f;
    char c;
    f = fopen(fname, "r");
    c = fgetc(f);
    while (c != EOF){
        printf("%c", c);
        c = fgetc(f);
    }
    fclose(f);
}

int main(int argc, char ** argv){
    if (argc < 3){
        printf("enter ./system <airports_file> <dists_file>\n");
        return 0;
    }

    //use info from files to create a graph
    int dir[26][26][26];
    int inv_dir[500];
    FILE * f;
    f = fopen(argv[1], "r");
    int V = 0;
    char buffer[50];
    while (fgets(buffer, 50, f) != NULL){
        buffer[3] = '\0';
        dir[buffer[0] - 'A'][buffer[1] - 'A'][buffer[2] - 'A'] = V;
        inv_dir[V] = (buffer[0] - 'A')*10000 + (buffer[1] - 'A')*100 + buffer[2] - 'A';
        V++;
    }

    int matrix[V][V];
    for (int i = 0; i < V; i++){
        for (int j = 0; j < V; j++){
            matrix[i][j] = 0;
        }
    }
    int edges[8000][2];
    int count = 0;
    FILE * g;
    g = fopen(argv[2], "r");
    int distance;
    char start[4];
    char end[4];
    int hash_start;
    int hash_end;
    while(fscanf(g, "%s %s %d", start, end, &distance) != EOF){
        hash_start = dir[start[0] - 'A'][start[1] - 'A'][start[2] - 'A'];
        hash_end = dir[end[0] - 'A'][end[1] - 'A'][end[2] - 'A'];
        matrix[hash_start][hash_end] = distance;
        matrix[hash_end][hash_start] = distance;
        edges[count][0] = hash_start;
        edges[count][1] = hash_end;
        count++;
    }

    int edge_list[count * 2][2];
    for (int i = 0; i < count; i++){
        edge_list[i][0] = edges[i][0];
        edge_list[i][1] = edges[i][1];
        edge_list[i + count][0] = edges[i][1];
        edge_list[i + count][1] = edges[i][0];
    }

    while(1){
        char command[50];
        printf("enter command> ");
        fgets(command, 50, stdin);
        char * cmd = NULL;
        char * depart = NULL;
        char * arrive = NULL;

        cmd = strtok(command, " \n");
        depart = strtok(NULL, " \n");
        arrive = strtok(NULL, " \n");

        if (!strcmp(cmd, "help")){
            printf("ALL COMMANDS ARE CASE SENSITIVE\nlist of commands\nhelp: prints this message\nquit: quits the program\nairports: prints airports serviced by FTA\ndistance <airport1> <airport2>: prints the shortest route from airport1 to airport2\n");
        }
        else if (!strcmp(cmd, "quit")){
            break;
        }
        else if (!strcmp(cmd, "airports")){
            airports(argv[1]);
        }
        else if (!strcmp(cmd, "distance")){
            //Bellman-Ford Implementation
            int dist[V];
            int last[V];
            for (int i = 0; i < V; i++){
                dist[i] = 1000000;
            }
            int depart_hash = dir[depart[0] - 'A'][depart[1] - 'A'][depart[2] - 'A'];
            int arrive_hash = dir[arrive[0] - 'A'][arrive[1] - 'A'][arrive[2] - 'A'];
            dist[depart_hash] = 0;

            for (int i = 0; i < V - 1; i++){
                for (int j = 0; j < 2 * count; j++){
                    int src = edge_list[j][0];
                    int dest = edge_list[j][1];
                    int w = matrix[src][dest];

                    if (dist[src] + w < dist[dest]){
                        dist[dest] = dist[src] + w;
                        last[dest] = src;
                    }
                }
            }

            printf("Total Distance is %d\n", dist[arrive_hash]);

            int backtrack = arrive_hash;
            int path[50];
            int legs = 0;
            while (backtrack != depart_hash){
                path[legs] = backtrack;
                backtrack = last[backtrack];
                legs++;
            }
            int for_path[legs + 1];
            for_path[0] = depart_hash;
            for (int i = 1; i < legs + 1; i++){
                for_path[i] = path[legs - i ];
            }

            int leave[3];
            int stop[3];
            char l[3];
            char s[3];
            for (int i = 0; i < legs; i++){
                leave[0] = inv_dir[for_path[i]]/10000;
                leave[1] = inv_dir[for_path[i]]/100 - 100*leave[0];
                leave[2] = inv_dir[for_path[i]] - 10000*leave[0] - 100*leave[1];

                stop[0] = inv_dir[for_path[i+1]]/10000;
                stop[1] = inv_dir[for_path[i+1]]/100 - 100*stop[0];
                stop[2] = inv_dir[for_path[i+1]] - 10000*stop[0] - 100*stop[1];

                for (int j = 0; j < 3; j++){
                    l[j] = 'A' + leave[j];
                    s[j] = 'A' + stop[j];
                }

                printf("%s -> %c%c%c %d\n", l, s[0], s[1], s[2], matrix[for_path[i]][for_path[i+1]]);
            }
        }
        else{
            printf("Invalid command, type help for info\n");
        }
    }

    return 0;
}
