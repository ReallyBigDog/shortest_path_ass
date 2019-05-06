#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*void print_array_2D(int **arr, int rows, int cols){
	for (int i=0; i<rows; i++){
		printf("[");
		for (int j=0; j<cols; j++)
			printf("%d ",arr[i][j]);
		printf("] ");
	}
	printf("\n");
}*/

/*typedef struct{
    int name;
}Vertex;*/

typedef struct{
    int weight;
    int verts[2];
}Edge;

typedef struct{
    int ** matrix;
}Graph;



/*struct Node{
    char * code;
    int hash;
    int index;
};

struct Edge{
    int weight;
    struct Node verts[2];
};

struct Graph{
    int ** matrix;
};

struct Graph makeGraph(struct * Node nodes, struct * Edge edges){
    struct Graph * graph = (struct Graph *)malloc(sizeof(struct Graph));
    for (int i = 0; i < V; i++){

    }
}*/

/*void printcodes(char * fname){
    FILE * f;
    f = fopen(fname, "r");
    char line[50];
    char code[4] = {0};
    while(fgets(line, sizeof(line), f) != NULL){
        sscanf(line, "%c%c%c", code[0], code[1], code[2]);
        printf("%s\n", line);
    }
}*/

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

void distance(char * fname, char * departure, char * arrival){
    /*int dist;
    char depart
    while (fscanf(f, "%s %s %d", ))*/
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
        //printf("%d, %d, %d\n", hash_start, hash_end, distance);
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

    //printing matrix
    /*for (int i=0; i<V; i++){
		printf("[");
		for (int j=0; j<V; j++)
			printf("%d ",matrix[i][j]);
		printf("]\n");
	}
	printf("\n");return 0;*/

    //printf("%d\n", dir['S'-'A']['F'-'A']['O'-'A']);
    /*int i = 0;
    int cur;
    while ((cur = fgetc(f)) != EOF){
        //cur = fgetc(f);
        char code[3];
        if (i < 3){
            i++;
            code[i] = cur;
            if (i == 3){
                //need to hash here
                printf("%s", code);
                V++;
            }
        }
    }*/
    /*char line[50];
    char code[3] = {0};
    while(fgets(line, sizeof(line), f) != NULL){
        sscanf(line, "%c%c%c\n", &code[0], &code[1], &code[2]);
        printf("%s\n", line);
        V++;
    }*/
    /*char buffer[1024], *p;
    if(fgets(buffer, sizeof(buffer), f)){
        if ((p = strchr(buffer, " "))){
            *p = '\0';
        }
        for (p = buffer; (* p); p++){
            char c = *p;
            printf("%c\n", c);
        }
    }*/



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
                        //printf("%d\n", dist[6]);
                        last[dest] = src;
                        //printf("%d, %d\n", src, dest);
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
                //printf("%d\n", path[legs]);
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
                //printf("%d %d\n", leave[0], i);
                leave[1] = inv_dir[for_path[i]]/100 - 100*leave[0];
                leave[2] = inv_dir[for_path[i]] - 10000*leave[0] - 100*leave[1];

                stop[0] = inv_dir[for_path[i+1]]/10000;
                //printf("%d %d\n", stop[0], i);
                stop[1] = inv_dir[for_path[i+1]]/100 - 100*stop[0];
                stop[2] = inv_dir[for_path[i+1]] - 10000*stop[0] - 100*stop[1];

                for (int j = 0; j < 3; j++){
                    l[j] = 'A' + leave[j];
                    s[j] = 'A' + stop[j];
                }

                printf("%s -> %c%c%c %d\n", l, s[0], s[1], s[2], matrix[for_path[i]][for_path[i+1]]);
            }
            //printf("%d %d\n", last[0], last[last[0]]);
            //print print last until we get to depart
            //then unhash and organize neatly

            //passes graph, depart, arrive
            //then finds shortest path
            //distance(argv[2], depart, arrive);
        }
        else{
            printf("Invalid command, type help for info\n");
        }
    }

    return 0;
}
