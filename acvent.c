#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define NEW_MEMORY(ptr, size)  {                                            \
                                    ptr = malloc(size);                     \
                                    if(ptr == NULL){                        \
                                        printf("Insufficient memory!\n");   \
                                        exit(1);                            \
                                    }                                       \
                                }                           
// end of NEW_MEMORY

#define VERTICAL_SEGMENT_DETECT     if(n->edge_broken == 1 && vertical_segmentation(n) == 1){                       \
                                        uchar left_found = 0;                                                       \
                                        uchar right_found = 0;                                                      \
                                        int index = 0;                                                              \
                                                                                                                    \
                                        while(index < HEIGHT){                                                      \
                                            if(left_found == 1){                                                    \
                                                break;                                                              \
                                            }                                                                       \
                                            struct Node tn = room[n->segment_y_path[index]];                        \
                                            if(tn.x > 0){                                                           \
                                                int j = 1;                                                          \
                                                while(j <= tn.x){                                                   \
                                                    if(n->omit[tn.position - j] == 0){                              \
                                                        left_found = 1;                                             \
                                                        break;                                                      \
                                                    };                                                              \
                                                    ++j;                                                            \
                                                }                                                                   \
                                            }                                                                       \
                                            ++index;                                                                \
                                        }                                                                           \
                                                                                                                    \
                                        index = 0;                                                                  \
                                        if(left_found == 1){                                                        \
                                            while(index < HEIGHT){                                                  \
                                                if(right_found == 1){                                               \
                                                    break;                                                          \
                                                }                                                                   \
                                                 struct Node tn = room[n->segment_y_path[index]];                   \
                                                 if(tn.x < WIDTH-1){                                                \
                                                     int j = tn.x;                                                  \
                                                     int k = 1;                                                     \
                                                     while(j < WIDTH-1){                                            \
                                                         if(n->omit[tn.position + k] == 0){                         \
                                                             right_found = 1;                                       \
                                                             break;                                                 \
                                                         }                                                          \
                                                         ++k;                                                       \
                                                         ++j;                                                       \
                                                     }                                                              \
                                                 }                                                                  \
                                            ++index;                                                                \
                                            }                                                                       \
                                        }                                                                           \
                                        if(left_found == 1 && right_found == 1){                                    \
                                            break;                                                                  \
                                        }                                                                           \
                                    }
// end define of VERTICAL_SEGMENT_DETECT                                

#define HORIZONTAL_SEGMENT_DETECT   if(n->edge_broken == 1 && horizontal_segmentation(n) == 1){                         \
                                    uchar top_found = 0;                                                                \
                                    uchar bottom_found = 0;                                                             \
                                    int index = 0;                                                                      \
                                                                                                                        \
                                     while(index < WIDTH){                                                              \
                                         if(top_found == 1){                                                            \
                                             break;                                                                     \
                                         }                                                                              \
                                         struct Node tn = room[n->segment_x_path[index]];                               \
                                         if(tn.y > 0){                                                                  \
                                             int j = 1;                                                                 \
                                             while(j <= tn.y){                                                          \
                                                 if(n->omit[tn.position - (j*WIDTH)] == 0){                             \
                                                     top_found = 1;                                                     \
                                                     break;                                                             \
                                                 };                                                                     \
                                                 ++j;                                                                   \
                                             }                                                                          \
                                         }                                                                              \
                                         ++index;                                                                       \
                                    }                                                                                   \
                                    index = 0;                                                                          \
                                    if(top_found == 1){                                                                 \
                                        while(index < WIDTH){                                                           \
                                            if(bottom_found == 1){                                                      \
                                                break;                                                                  \
                                            }                                                                           \
                                            struct Node tn = room[n->segment_x_path[index]];                            \
                                            if(tn.y < HEIGHT-1){                                                        \
                                                int j = tn.y;                                                           \
                                                int k = 1;                                                              \
                                                while(j < HEIGHT-1){                                                    \
                                                    if(n->omit[tn.position + (k*WIDTH)] == 0){                          \
                                                        bottom_found = 1;                                               \
                                                        break;                                                          \
                                                    }                                                                   \
                                                    ++k;                                                                \
                                                    ++j;                                                                \
                                                }                                                                       \
                                            }                                                                           \
                                            ++index;                                                                    \
                                        }                                                                               \
                                    }                                                                                   \
                                    if(top_found == 1 && bottom_found == 1){                                            \
                                        break;                                                                          \
                                    }                                                                                   \
                                }
// end of HORIZONTAL_SEGMENT_DETECT

#define PROCESS_NEIGHBOUR(x)    {                                                                                           \
                    if(n->omit[x] != 1 && !(room[x].type == END && n->path_count < GLOBAL_PROPERTIES.max_path_length-1)){   \
                        struct LLNode* nn;                                                                                  \
                        COPY_LLNODE(n,nn);                                                                                  \
                        nn->position = x;                                                                                   \
                        push(list, nn);                                                                                     \
                    }                                                                                                       \
                }
// end of PROCESS_NEIGHBOUR

#define COPY_LLNODE(src, dst)   {                                                                       \
                    NEW_MEMORY(dst, sizeof(struct LLNode));                                             \
                                                                                                        \
                    dst->position = src->position;                                                      \
                    dst->path_count = src->path_count;                                                  \
                    dst->edge_broken = src->edge_broken;                                                \
                                                                                                        \
                    NEW_MEMORY(dst->omit,sizeof(uchar)*ROOMSIZE);                                       \
                    NEW_MEMORY(dst->segment_x,sizeof(uchar)*WIDTH);                                     \
                    NEW_MEMORY(dst->segment_y,sizeof(uchar)*HEIGHT);                                    \
                    NEW_MEMORY(dst->segment_x_path,sizeof(uchar)*WIDTH);                                \
                    NEW_MEMORY(dst->segment_y_path,sizeof(uchar)*HEIGHT);                               \
                                                                                                        \
                    memcpy(dst->omit, src->omit,sizeof(uchar)*ROOMSIZE);                                \
                    memcpy(dst->segment_x, src->segment_x,sizeof(uchar)*WIDTH);                         \
                    memcpy(dst->segment_y, src->segment_y,sizeof(uchar)*HEIGHT);                        \
                    memcpy(dst->segment_x_path, src->segment_x_path,sizeof(uchar)*WIDTH);               \
                    memcpy(dst->segment_y_path, src->segment_y_path,sizeof(uchar)*HEIGHT);              \
                                                                                                        \
                    dst->next = NULL;                                                                   \
                    }
// end of COPY_LLNODE

#define DESTROY_LLNODE(node)  {                                                                         \
                        free(node->omit);                                                               \
                        node->omit = NULL;                                                              \
                        free(node->segment_x);                                                          \
                        node->segment_x = NULL;                                                         \
                        free(node->segment_y);                                                          \
                        node->segment_y = NULL;                                                         \
                        free(node->segment_x_path);                                                     \
                        node->segment_x_path = NULL;                                                    \
                        free(node->segment_y_path);                                                     \
                        node->segment_y_path = NULL;                                                    \
                        node->next = NULL;                                                              \
                        free(node);                                                                     \
                        node = NULL;                                                                    \
                }
// end of DESTROY_LLNODE

#define ROOMSIZE GLOBAL_PROPERTIES.size
#define WIDTH GLOBAL_PROPERTIES.width
#define HEIGHT GLOBAL_PROPERTIES.height

typedef unsigned char uchar;
typedef signed char schar;

enum nodetype {
	TOPEDGE,
    BOTTOMEDGE,
    LEFTEDGE,
    RIGHTEDGE,
    FOURWAY,
    OMIT,
    TOPLEFTCORNER,
    TOPRIGHTCORNER,
    BOTTOMLEFTCORNER,
    BOTTOMRIGHTCORNER,
    START,
    END
};

struct Node {
    enum nodetype type;
    uchar x;
    uchar y;
    uchar position;
    uchar value;
    //uchar omit;
};

struct Globals {
    uchar max_path_length; // HxW-omission_occurences
    int start;
    int end;
    schar height;
    schar width;
    uchar size;
};

struct Globals GLOBAL_PROPERTIES;


/*struct Instance {
    uchar path_count;
    uchar edge_broken;
    uchar *segment_x;
    uchar *segment_y;
    uchar *segment_x_path;
    uchar *segment_y_path;
};*/

struct LLNode {
    uchar position;
    uchar path_count;
    uchar edge_broken;
    uchar *omit;
    uchar *segment_x;
    uchar *segment_y;
    uchar *segment_x_path;
    uchar *segment_y_path;

    struct LLNode* next;
};

struct LList {
    int count;
    struct LLNode* start;
};

// struct Node* copy_room_map(struct Node* room_map) {
//     struct Node* return_map;
//     NEW_MEMORY(return_map,sizeof(struct Node)*ROOMSIZE); 
//     memcpy(return_map, room_map, ((sizeof(struct Node))*ROOMSIZE));
//     return return_map;
// }

struct LLNode* new_llnode(){
    struct LLNode* node;
    NEW_MEMORY(node, sizeof(struct LLNode));
    node->position = 0;
    node->path_count = 0;
    node->edge_broken = 0;
    NEW_MEMORY(node->omit, sizeof(uchar)*ROOMSIZE);
    NEW_MEMORY(node->segment_x,sizeof(uchar)*WIDTH);
    NEW_MEMORY(node->segment_y,sizeof(uchar)*HEIGHT);
    NEW_MEMORY(node->segment_x_path,sizeof(uchar)*WIDTH);
    NEW_MEMORY(node->segment_y_path,sizeof(uchar)*HEIGHT);

    uchar index = 0;
    while(index < WIDTH){
        node->segment_x[index] = 0;
        node->segment_x_path[index] = 0;
        ++index;
    }
    index = 0;
    while(index < HEIGHT){
        node->segment_y[index] = 0;
        node->segment_y_path[index] = 0;
        ++index;
    }
    index = 0;
    while(index < ROOMSIZE){
        node->omit[index] = 0;
        ++index;
    }
    
    node->next = NULL;
    return node;
}

struct LLNode* copy_llnode(struct LLNode* oldnode){
    struct LLNode* node;
    NEW_MEMORY(node, sizeof(struct LLNode));
    
    node->position = oldnode->position;
    node->path_count = oldnode->path_count;
    node->edge_broken = oldnode->edge_broken;
    
    NEW_MEMORY(node->omit, sizeof(uchar)*ROOMSIZE);
    NEW_MEMORY(node->segment_x,sizeof(uchar)*WIDTH);
    NEW_MEMORY(node->segment_y,sizeof(uchar)*HEIGHT);
    NEW_MEMORY(node->segment_x_path,sizeof(uchar)*WIDTH);
    NEW_MEMORY(node->segment_y_path,sizeof(uchar)*HEIGHT);
    
    memcpy(node->omit, oldnode->omit, sizeof(uchar)*ROOMSIZE);
    memcpy(node->segment_x, oldnode->segment_x,sizeof(uchar)*WIDTH);
    memcpy(node->segment_y, oldnode->segment_y,sizeof(uchar)*HEIGHT);
    memcpy(node->segment_x_path, oldnode->segment_x_path,sizeof(uchar)*WIDTH);
    memcpy(node->segment_y_path, oldnode->segment_y_path,sizeof(uchar)*HEIGHT);
    
    node->next = NULL;
    return node;
}

void destroy_llnode(struct LLNode* node){
    free(node->omit);
    node->omit = NULL;
    free(node->segment_x);
    node->segment_x = NULL;
    free(node->segment_y);
    node->segment_y = NULL;
    free(node->segment_x_path);
    node->segment_x_path = NULL;
    free(node->segment_y_path);
    node->segment_y_path = NULL;
    
    node->next = NULL;
    free(node);
    node = NULL;
}

struct LList* new_list(void){
    struct LList* list;
    NEW_MEMORY(list,sizeof(struct LList));
    list->count = 0;
    list->start = NULL;
    return list;
}

void push(struct LList* list, struct LLNode* node){
    node->next = list->start;
    list->start = node;
    list->count = list->count +1;
}

struct LLNode* pop(struct LList* list){
    if(list->count > 0){
        struct LLNode* node = list->start;
        list->start = node->next;
        list->count = list->count - 1;
        node->next = NULL;
        return node;
    }
}

void destroy_list(struct LList* list){
    while(list->count > 0){
        struct LLNode* node = pop(list);
        destroy_llnode(node);
    }
    free(list);
    list = NULL;
}


void init_properties(){
    GLOBAL_PROPERTIES.max_path_length = 0;
    GLOBAL_PROPERTIES.start = -1;
    GLOBAL_PROPERTIES.end = -1;
    HEIGHT = 0;
    WIDTH = 0;
    GLOBAL_PROPERTIES.size = 0;
}

// struct Instance* new_instance(void) {
//     struct Instance* return_instance;
//     NEW_MEMORY(return_instance, sizeof(struct Instance));
//     
//     return_instance->path_count = 0;
//     return_instance->edge_broken = 0;
//     
//     NEW_MEMORY(return_instance->segment_x,sizeof(uchar)*WIDTH);
//     NEW_MEMORY(return_instance->segment_y,sizeof(uchar)*HEIGHT);
//     NEW_MEMORY(return_instance->segment_x_path,sizeof(uchar)*WIDTH);
//     NEW_MEMORY(return_instance->segment_y_path,sizeof(uchar)*HEIGHT);
// 
//     uchar index = 0;
//     while(index < WIDTH){
//         return_instance->segment_x[index] = 0;
//         return_instance->segment_x_path[index] = 0;
//         ++index;
//     }
//     index = 0;
//     while(index < HEIGHT){
//         return_instance->segment_y[index] = 0;
//         return_instance->segment_y_path[index] = 0;
//         ++index;
//     }
//     
//     return return_instance;
// }
// 
// struct Instance* copy_instance(struct Instance* inst) {
//     struct Instance* return_instance;
//     NEW_MEMORY(return_instance, sizeof(struct Instance));
//      
//      return_instance->path_count = inst->path_count;
//      return_instance->edge_broken = inst->edge_broken;
//      
//      NEW_MEMORY(return_instance->segment_x,sizeof(uchar)*WIDTH);
//      NEW_MEMORY(return_instance->segment_y,sizeof(uchar)*HEIGHT);
//      NEW_MEMORY(return_instance->segment_x_path,sizeof(uchar)*WIDTH);
//      NEW_MEMORY(return_instance->segment_y_path,sizeof(uchar)*HEIGHT);
//      
//      memcpy(return_instance->segment_x, inst->segment_x,sizeof(uchar)*WIDTH);
//      memcpy(return_instance->segment_y, inst->segment_y,sizeof(uchar)*HEIGHT);
//      memcpy(return_instance->segment_x_path, inst->segment_x_path,sizeof(uchar)*WIDTH);
//      memcpy(return_instance->segment_y_path, inst->segment_y_path,sizeof(uchar)*HEIGHT);
//      
//      return return_instance;
// }
// 
// void destroy_instance(struct Instance* inst) {
//     free(inst->segment_x);
//     free(inst->segment_y);
//     free(inst->segment_x_path);
//     free(inst->segment_y_path);
//     free(inst);
//     inst = NULL;
// }

int vertical_segmentation(struct LLNode* node){
    schar index = 0;
    schar total = 0;
    while(index < HEIGHT){
        total = total + node->segment_y[index];
        ++index;
    }
    if(total == HEIGHT){
        return 1;
    }
    return 0;
}

int horizontal_segmentation(struct LLNode* node){
    schar index = 0;
    schar total = 0;
    while(index < WIDTH){
        total = total + node->segment_x[index];
        ++index;
    }
    if(total == WIDTH){
        return 1;
    }
    return 0;
}

int search_path(struct Node* room_map, struct LLNode* node) {
    struct LLNode* new_inst;
    COPY_LLNODE(node, new_inst);
    
    new_inst->omit[new_inst->position] = 1;
    
    new_inst->segment_x[room_map[new_inst->position].x] = 1;
    new_inst->segment_y[room_map[new_inst->position].y] = 1;
    new_inst->segment_x_path[room_map[new_inst->position].x] = new_inst->position;
    new_inst->segment_y_path[room_map[new_inst->position].y] = new_inst->position;
    
    new_inst->path_count = new_inst->path_count +1;
    
    int leftcount = 0;
    int rightcount = 0;
    int topcount = 0;
    int bottomcount = 0;
    
    //printf("current_position %i \n", current_position);
    switch(room_map[new_inst->position].type)
    {
        case TOPLEFTCORNER:
            //VERTICAL_SEGMENT_DETECT;
            //HORIZONTAL_SEGMENT_DETECT;
            if(new_inst->omit[new_inst->position+1] != 1){
                new_inst->position = new_inst->position+1;
                rightcount = search_path(room_map, new_inst);
            }
            if(new_inst->omit[new_inst->position+WIDTH] != 1){
                new_inst->position = new_inst->position+WIDTH; 
                bottomcount = search_path(room_map, new_inst);
            }
            break;
            
        case TOPEDGE:    
            //VERTICAL_SEGMENT_DETECT;
            if(new_inst->omit[new_inst->position-1] != 1){
                new_inst->position = new_inst->position-1;
                leftcount = search_path(room_map, new_inst);
            }
            if(new_inst->omit[new_inst->position+1] != 1){
                new_inst->position = new_inst->position+1;
                rightcount = search_path(room_map, new_inst);
            }
            if(new_inst->omit[new_inst->position+WIDTH] != 1){
                new_inst->position = new_inst->position+WIDTH; 
                bottomcount = search_path(room_map, new_inst);
            }
            break;
            
        case BOTTOMEDGE:
            //VERTICAL_SEGMENT_DETECT;
            if(new_inst->omit[new_inst->position-1] != 1){
                new_inst->position = new_inst->position-1;
                leftcount = search_path(room_map, new_inst);
            }
            if(new_inst->omit[new_inst->position-WIDTH] != 1){
                new_inst->position = new_inst->position-WIDTH; 
                topcount = search_path(room_map, new_inst);
            }
            if(new_inst->omit[new_inst->position+1] != 1){
                new_inst->position = new_inst->position+1;
                rightcount = search_path(room_map, new_inst);
            }
            break;
            
        case LEFTEDGE:
            //HORIZONTAL_SEGMENT_DETECT;
            if(new_inst->omit[new_inst->position-WIDTH] != 1){
                new_inst->position = new_inst->position-WIDTH; 
                topcount = search_path(room_map, new_inst);
            }
            if(new_inst->omit[new_inst->position+1] != 1){
                new_inst->position = new_inst->position+1;
                rightcount = search_path(room_map, new_inst);
            }
            if(new_inst->omit[new_inst->position+WIDTH] != 1){
                new_inst->position = new_inst->position+WIDTH; 
                bottomcount = search_path(room_map, new_inst);
            }
            break;
            
        case RIGHTEDGE:
            //HORIZONTAL_SEGMENT_DETECT;
            if(new_inst->omit[new_inst->position-1] != 1){
                new_inst->position = new_inst->position-1;
                leftcount = search_path(room_map, new_inst);
            }
            if(new_inst->omit[new_inst->position-WIDTH] != 1){
                new_inst->position = new_inst->position-WIDTH; 
                topcount = search_path(room_map, new_inst);
            }
            if(new_inst->omit[new_inst->position+WIDTH] != 1){
                new_inst->position = new_inst->position+WIDTH; 
                bottomcount = search_path(room_map, new_inst);
            }
            break;
        
        case TOPRIGHTCORNER:
            //VERTICAL_SEGMENT_DETECT;
            //HORIZONTAL_SEGMENT_DETECT;
            if(new_inst->omit[new_inst->position-1] != 1){
                new_inst->position = new_inst->position-1;
                leftcount = search_path(room_map, new_inst);
            }
            if(new_inst->omit[new_inst->position+WIDTH] != 1){
                new_inst->position = new_inst->position+WIDTH; 
                bottomcount = search_path(room_map, new_inst);
            }
            break;
        
        case BOTTOMLEFTCORNER:
            //VERTICAL_SEGMENT_DETECT;
            //HORIZONTAL_SEGMENT_DETECT;
            if(new_inst->omit[new_inst->position-WIDTH] != 1){
                new_inst->position = new_inst->position-WIDTH; 
                topcount = search_path(room_map, new_inst);
            }
            if(new_inst->omit[new_inst->position+1] != 1){
                new_inst->position = new_inst->position+1;
                rightcount = search_path(room_map, new_inst);
            }
            break;
        
        case BOTTOMRIGHTCORNER:
            //VERTICAL_SEGMENT_DETECT;
            //HORIZONTAL_SEGMENT_DETECT;
            if(new_inst->omit[new_inst->position-1] != 1){
                new_inst->position = new_inst->position-1;
                leftcount = search_path(room_map, new_inst);
            }
            if(new_inst->omit[new_inst->position-WIDTH] != 1){
                new_inst->position = new_inst->position-WIDTH; 
                topcount = search_path(room_map, new_inst);
            }
            break;
            
        case FOURWAY:
            new_inst->edge_broken = 1;
            if(new_inst->omit[new_inst->position-1] != 1){
                new_inst->position = new_inst->position-1;
                leftcount = search_path(room_map, new_inst);
            }
            if(new_inst->omit[new_inst->position-WIDTH] != 1){
                new_inst->position = new_inst->position-WIDTH; 
                topcount = search_path(room_map, new_inst);
            }
            if(new_inst->omit[new_inst->position+1] != 1){
                new_inst->position = new_inst->position+1;
                rightcount = search_path(room_map, new_inst);
            }
             if(new_inst->omit[new_inst->position+WIDTH] != 1){
                 new_inst->position = new_inst->position+WIDTH; 
                 bottomcount = search_path(room_map, new_inst);
             }
             break;
             
        case END:
            if(new_inst->path_count == GLOBAL_PROPERTIES.max_path_length+1){
                bottomcount = 1;
            }
            break;
            
    }    
    
    DESTROY_LLNODE(new_inst);
    return topcount + bottomcount + leftcount + rightcount;
}

int main() {
    init_properties();
    
    int n = 0;
    int count = 1;
    
    while (scanf("%d", &n) == 1){
        if(count == 1){
            WIDTH = n;
        }
        if(count == 2){
            HEIGHT = n;
            break;
        }
        ++count;
    }
    if(WIDTH < 0 || HEIGHT < 0){
        printf("You can't have negative sized rooms\n");
        exit(1);
    }
    
    if(WIDTH == 0 || HEIGHT == 0){
        printf("You can't have a room with a zero width or height\n");
        exit(1);
    }
    
    if(WIDTH == 1 && HEIGHT == 1) {
        printf("You need at least 2 rooms\n");
        exit(1);
    }
    if(WIDTH > 15 || HEIGHT > 15){
        printf("Width and Height are limited to 15 due to memory and time constraints\n");
        exit(1);
    }
    
    ROOMSIZE = WIDTH * HEIGHT;
    
    //int array[width][height];
    count = 0;
    schar h = 0;
    schar w = 0;
    uchar omission_occurrences = 0;
    uchar path_length = 0; 
    uchar omit_list[ROOMSIZE];
    int c = 0;
    while(c < ROOMSIZE){
        omit_list[c] = 0;
        ++c;
    }
    struct Node room[ROOMSIZE];
    //struct Instance* inst = new_instance();
    //inst->path_count = 1;

    while (scanf("%d", &n) == 1){
        if(w == WIDTH){
            w = 0;
            ++h;
        }
        room[count].x = w;
        room[count].y = h;
        room[count].value = n;
        room[count].position = count;

        if(n < 0 || n > 3){
            printf("Invalid input for room types\n");
            exit(1);
        }
        if(n == 1){
            ++omission_occurrences;
            room[count].type = OMIT;
            omit_list[count] = 1;
        }
        if(n == 0 || n == 2 || n == 3){
            ++path_length;
            room[count].type = FOURWAY;
            if((0 < w < WIDTH-1) && h == 0){
                room[count].type = TOPEDGE;
            }
            if((0 < w < WIDTH-1) && h == HEIGHT-1){
                room[count].type = BOTTOMEDGE;
            }
            if(w == 0 && (0 < h < HEIGHT-1)){
                room[count].type = LEFTEDGE;
            }
            if(w == WIDTH-1 && (0 < h < HEIGHT-1)){
                room[count].type = RIGHTEDGE;
            }
            if(w == 0 && h == 0){
                room[count].type = TOPLEFTCORNER;
            }
            if(w == 0 && h == HEIGHT-1){
                room[count].type = BOTTOMLEFTCORNER;
            }
            if(w == WIDTH-1 && h == 0){
                room[count].type = TOPRIGHTCORNER;
            }
            if(w == WIDTH-1 && h == HEIGHT-1){
                room[count].type = BOTTOMRIGHTCORNER;
            }
        }
        if(n == 2){
            if(GLOBAL_PROPERTIES.start == -1){
                GLOBAL_PROPERTIES.start = count;
            } else {
                printf("You can only have 1 intake\n");
                exit(1);
            }
            //room[count].type = START;
            //room[count].start = 1;
            //--path_length;
        }
        if(n == 3){
            if(GLOBAL_PROPERTIES.end == -1){
                GLOBAL_PROPERTIES.end = count;
            } else {
                printf("You can only have 1 ac unit\n");
                exit(1);
            }
            
            room[count].type = END;
            //--path_length;
            //room[count].end = 1;
        }  
        ++count;
        ++w;
        if(count > ROOMSIZE-1){
            break;
        }
    }    
    
    if(GLOBAL_PROPERTIES.start == -1){
        printf("There has to be a intake duct marked with a value of 2\n");
        exit(1);
    }
    if(GLOBAL_PROPERTIES.end == -1){
        printf("There has to be an air conditioner marked with a value of 3\n");
        exit(1);
    }
    if(path_length != (ROOMSIZE-omission_occurrences)){
        printf("Error detected in input values\n");
        exit(1);
    } else {
        GLOBAL_PROPERTIES.max_path_length = path_length;
    } 
    
    int total_paths = 0;
    struct LList* list = new_list();
    struct LLNode* node = new_llnode();
    node->position = GLOBAL_PROPERTIES.start;
    memcpy(node->omit, omit_list,sizeof(uchar)*ROOMSIZE);
    push(list, node);
    while(list->count > 0){
        struct LLNode* n = pop(list);
        //printf("position %i \n", n->position);
        n->omit[n->position] = 1;
        n->path_count = n->path_count + 1;
        n->segment_x[room[n->position].x] = 1;
        n->segment_y[room[n->position].y] = 1;
        n->segment_x_path[room[n->position].x] = n->position;
        n->segment_y_path[room[n->position].y] = n->position;
        switch(room[n->position].type)
        {
            case TOPEDGE:
                //VERTICAL_SEGMENT_DETECT        
                PROCESS_NEIGHBOUR(n->position-1);
                PROCESS_NEIGHBOUR(n->position+1);
                PROCESS_NEIGHBOUR(n->position+WIDTH);
                break;
            case BOTTOMEDGE:
                //VERTICAL_SEGMENT_DETECT
                PROCESS_NEIGHBOUR(n->position-1);
                PROCESS_NEIGHBOUR(n->position-WIDTH);
                PROCESS_NEIGHBOUR(n->position+1);
                break;
            
            case LEFTEDGE:
                //HORIZONTAL_SEGMENT_DETECT
                PROCESS_NEIGHBOUR(n->position-WIDTH);
                PROCESS_NEIGHBOUR(n->position+1);
                PROCESS_NEIGHBOUR(n->position+WIDTH);
                break;
            
            case RIGHTEDGE:
                //HORIZONTAL_SEGMENT_DETECT
                PROCESS_NEIGHBOUR(n->position-1);
                PROCESS_NEIGHBOUR(n->position-WIDTH);
                PROCESS_NEIGHBOUR(n->position+WIDTH);
                break;
                
            case FOURWAY:
                n->edge_broken = 1;
                PROCESS_NEIGHBOUR(n->position-1);
                PROCESS_NEIGHBOUR(n->position-WIDTH);
                PROCESS_NEIGHBOUR(n->position+1);
                PROCESS_NEIGHBOUR(n->position+WIDTH);
                break;
                
            case TOPLEFTCORNER:
                //VERTICAL_SEGMENT_DETECT
                //HORIZONTAL_SEGMENT_DETECT
                PROCESS_NEIGHBOUR(n->position+1);
                PROCESS_NEIGHBOUR(n->position+WIDTH);
                break;
                
            case TOPRIGHTCORNER:
                //VERTICAL_SEGMENT_DETECT
                //HORIZONTAL_SEGMENT_DETECT
                PROCESS_NEIGHBOUR(n->position-1);
                PROCESS_NEIGHBOUR(n->position+WIDTH);
                break;
                    
            case BOTTOMLEFTCORNER:
                //VERTICAL_SEGMENT_DETECT
                //HORIZONTAL_SEGMENT_DETECT
                PROCESS_NEIGHBOUR(n->position-WIDTH);
                PROCESS_NEIGHBOUR(n->position+1);
                break;
                
            case BOTTOMRIGHTCORNER:
                //VERTICAL_SEGMENT_DETECT
                //HORIZONTAL_SEGMENT_DETECT
                PROCESS_NEIGHBOUR(n->position-1);
                PROCESS_NEIGHBOUR(n->position-WIDTH);
                break;
            
            case OMIT:
                printf("impossible!\n");
                break;
                
            case END:
                if(n->path_count == GLOBAL_PROPERTIES.max_path_length){
                    ++total_paths;
                }
                break;
        }
        DESTROY_LLNODE(n);
        //destroy_llnode(n);
    }
    
    //int total_paths = search_path(GLOBAL_PROPERTIES.start, room, inst);
    printf("%i\n", total_paths);
    //destroy_instance(inst);
    destroy_list(list);
    return 0;
}
