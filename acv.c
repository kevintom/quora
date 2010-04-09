#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define NEW_MEMORY(ptr, size)  {                                            \
                                    ptr = malloc(size);                     \
                                    if(ptr == NULL){                        \
                                        printf("Insufficient memory!\n");   \
                                        exit(1);                            \
                                    }                                       \
                                }                           
// end of NEW_MEMORY

#define VERTICAL_SEGMENT_DETECT     if(node->edge_broken == 1 && vertical_segmentation(node) == 1){                 \
                                        uchar left_found = 0;                                                       \
                                        uchar right_found = 0;                                                      \
                                        int left_value = 0;                                                         \
                                        int right_value = 0;                                                        \
                                        int index = 0;                                                              \
                                                                                                                    \
                                        while(index < HEIGHT){                                                      \
                                            if(left_found == 1){                                                    \
                                                break;                                                              \
                                            }                                                                       \
                                            struct Node tn = room[node->segment_y_path[index]];                     \
                                            if(tn.x > 0){                                                           \
                                                int j = 1;                                                          \
                                                while(j <= tn.x){                                                   \
                                                    if(node->omit[tn.position - j] == 0){                           \
                                                        left_found = 1;                                             \
                                                        left_value = tn.position-j;                                 \
                                                        break;                                                      \
                                                    }                                                               \
                                                    ++j;                                                            \
                                                }                                                                   \
                                            }                                                                       \
                                            ++index;                                                                \
                                        }                                                                           \
                                                                                                                    \
                                        index = HEIGHT-1;                                                           \
                                        if(left_found == 1){                                                        \
                                            while(index >= 0){                                                       \
                                                if(right_found == 1){                                               \
                                                    break;                                                          \
                                                }                                                                   \
                                                 struct Node tn = room[node->segment_y_path[index]];                \
                                                 if(tn.x < WIDTH-1){                                                \
                                                     int j = tn.x;                                                  \
                                                     int k = 1;                                                     \
                                                     while(j < WIDTH-1){                                            \
                                                         if(node->omit[tn.position + k] == 0){                      \
                                                            right_found = 1;                                        \
                                                            right_value = tn.position +k;                           \
                                                            break;                                                  \
                                                         }                                                          \
                                                         ++k;                                                       \
                                                         ++j;                                                       \
                                                     }                                                              \
                                                 }                                                                  \
                                            --index;                                                                \
                                            }                                                                       \
                                        }                                                                           \
                                        if(left_found == 1 && right_found == 1){                                    \
                                            int map[ROOMSIZE];                                                      \
                                            int b = 0;                                                              \
                                            while(b < ROOMSIZE){                                                    \
                                                map[b] = 0;                                                         \
                                                ++b;                                                                \
                                            }                                                                       \
                                            int a = floodfill(node, map, left_value, right_value);                  \
                                            if(a != 1){                                                             \
                                                return 0;                                                           \
                                            }                                                                       \
                                        }                                                                           \
                                    }
// end define of VERTICAL_SEGMENT_DETECT                                

#define HORIZONTAL_SEGMENT_DETECT   if(node->edge_broken == 1 && horizontal_segmentation(node) == 1){                   \
                                    uchar top_found = 0;                                                                \
                                    uchar bottom_found = 0;                                                             \
                                    int index = 0;                                                                      \
                                    int top_value = 0;                                                                  \
                                    int bottom_value = 0;                                                               \
                                                                                                                        \
                                     while(index < WIDTH){                                                              \
                                         if(top_found == 1){                                                            \
                                             break;                                                                     \
                                         }                                                                              \
                                         struct Node tn = room[node->segment_x_path[index]];                            \
                                         if(tn.y > 0){                                                                  \
                                             int j = 1;                                                                 \
                                             while(j <= tn.y){                                                          \
                                                 if(node->omit[tn.position - (j*WIDTH)] == 0){                          \
                                                     top_found = 1;                                                     \
                                                     top_value = tn.position -(j*WIDTH);                                \
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
                                            struct Node tn = room[node->segment_x_path[index]];                         \
                                            if(tn.y < HEIGHT-1){                                                        \
                                                int j = tn.y;                                                           \
                                                int k = 1;                                                              \
                                                while(j < HEIGHT-1){                                                    \
                                                    if(node->omit[tn.position + (k*WIDTH)] == 0){                       \
                                                        bottom_found = 1;                                               \
                                                        bottom_value = tn.position+(k*WIDTH);                           \
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
                                        int map[ROOMSIZE];                                                              \
                                        int b = 0;                                                                      \
                                        while(b < ROOMSIZE){                                                            \
                                            map[b] = 0;                                                                 \
                                            ++b;                                                                        \
                                        }                                                                               \
                                        int a = floodfill(node, map, top_value, bottom_value);                          \
                                        if(a != 1){                                                                     \
                                            return 0;                                                                   \
                                        }                                                                               \
                                    }                                                                                   \
                                }
// end of HORIZONTAL_SEGMENT_DETECT

#define PROCESS_NEIGHBOUR(x, directcount)   if(node->omit[x] != 1 && !((x) == EXIT && node->path_count < GLOBAL_PROPERTIES.max_path_length-1)){     \
                                                if((x) == EXIT && node->path_count == GLOBAL_PROPERTIES.max_path_length - 1){                       \
                                                    directcount = 1;                                                                                \
                                                } else {                                                                                            \
                                                    struct LLNode* nn;                                                                              \
                                                    COPY_LLNODE(node,nn);                                                                           \
                                                    nn->position = (x);                                                                             \
                                                    directcount = search_path(room, nn);                                                            \
                                                    DESTROY_LLNODE(nn);                                                                             \
                                                }                                                                                                   \
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
#define EXIT GLOBAL_PROPERTIES.end

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
struct Node* ROOM;


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
        DESTROY_LLNODE(node);
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
    ROOMSIZE = 0;
}

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

int left_u_pitcheck(struct LLNode* node){
    if(ROOM[node->position].x < WIDTH-2 && ROOM[node->position].y < HEIGHT-2){
        if(node->omit[node->position+1] == 0 && 
            node->position+1 != EXIT &&
            node->omit[node->position+WIDTH+1] == 0 && 
            node->position+WIDTH+1 != EXIT &&
            node->omit[node->position] == 1 &&
            node->omit[node->position+WIDTH] == 1 && 
            node->omit[node->position+WIDTH+WIDTH+1] == 1 &&
            node->omit[node->position+2] == 1 &&
            node->omit[node->position+WIDTH+2] ==1){
            return 1;
        }
    }
    return 0;
}

int right_u_pitcheck(struct LLNode* node){
    if(ROOM[node->position].x > 1 && ROOM[node->position].y < HEIGHT-2){
        if(node->omit[node->position-1] == 0 && 
            node->position-1 != EXIT &&
            node->omit[node->position+WIDTH-1] == 0 && 
            node->position+WIDTH-1 != EXIT &&
            node->omit[node->position] == 1 &&
            node->omit[node->position+WIDTH] == 1 &&
            node->omit[node->position+WIDTH+WIDTH-1] == 1 &&
            node->omit[node->position-2] == 1 &&
            node->omit[node->position+WIDTH-2] ==1){
            return 1;
        }
    }
    return 0;
}

int left_a_pitcheck(struct LLNode* node){
    if(ROOM[node->position].x < WIDTH-2 && ROOM[node->position].y > 1){
        if(node->omit[node->position+1] == 0 && 
            node->position+1 != EXIT &&
            node->omit[node->position-WIDTH+1] == 0 && 
            node->position-WIDTH+1 != EXIT &&
            node->omit[node->position] == 1 &&
            node->omit[node->position-WIDTH] == 1 &&
            node->omit[node->position-WIDTH-WIDTH+1] == 1 &&
            node->omit[node->position+2] == 1 &&
            node->omit[node->position-WIDTH+2] ==1){
            return 1;
        }
    }
    return 0;
}

int right_a_pitcheck(struct LLNode* node){
    if(ROOM[node->position].x > 1 && ROOM[node->position].y > 1){
        if(node->omit[node->position-1] == 0 && 
            node->position-1 != EXIT &&
            node->omit[node->position-WIDTH-1] == 0 && 
            node->position-WIDTH-1 != EXIT &&
            node->omit[node->position] == 1 &&
            node->omit[node->position-WIDTH] == 1 &&
            node->omit[node->position-WIDTH-WIDTH-1] == 1 &&
            node->omit[node->position-2] == 1 &&
            node->omit[node->position-WIDTH-2] ==1){
            return 1;
        }
    }
    return 0;
}

int top_c_pitcheck(struct LLNode* node){
    if(ROOM[node->position].x > 1 && ROOM[node->position].y < HEIGHT-2 ){
        if(node->omit[node->position+WIDTH] == 0 && 
            node->position+WIDTH != EXIT &&
            node->omit[node->position+WIDTH-1] == 0 && 
            node->position+WIDTH-1 != EXIT &&
            node->omit[node->position] == 1 &&
            node->omit[node->position-1] == 1 &&
            node->omit[node->position-2+WIDTH] == 1 &&
            node->omit[node->position+WIDTH+WIDTH] == 1 &&
            node->omit[node->position+WIDTH+WIDTH-1] ==1){
            return 1;
        }
    }
    return 0;
}

int bottom_c_pitcheck(struct LLNode* node){
    if(ROOM[node->position].x > 1 && ROOM[node->position].y > 1){
        if(node->omit[node->position-WIDTH] == 0 && 
            node->position-WIDTH != EXIT &&
            node->omit[node->position-WIDTH-1] == 0 &&
            node->position-WIDTH-1 != EXIT &&
            node->omit[node->position] == 1 &&
            node->omit[node->position-1] == 1 &&
            node->omit[node->position-2-WIDTH] == 1 &&
            node->omit[node->position-WIDTH-WIDTH] == 1 &&
            node->omit[node->position-WIDTH-WIDTH-1] ==1){
            return 1;
        }
    }
    return 0; 
}

int top_d_pitcheck(struct LLNode* node){
    if(ROOM[node->position].x < WIDTH-2 && ROOM[node->position].y < HEIGHT-2 ){
        if(node->omit[node->position+WIDTH] == 0 && 
            node->position+WIDTH != EXIT &&
            node->omit[node->position+WIDTH+1] == 0 && 
            node->position+WIDTH+1 != EXIT &&
            node->omit[node->position] == 1 &&
            node->omit[node->position+1] == 1 &&
            node->omit[node->position+2+WIDTH] == 1 &&
            node->omit[node->position+WIDTH+WIDTH] == 1 &&
            node->omit[node->position+WIDTH+WIDTH+1] ==1){
            return 1;
        }
    }
    return 0;
}

int bottom_d_pitcheck(struct LLNode* node){
    if(ROOM[node->position].x < WIDTH-2 && ROOM[node->position].y > 1){
        if(node->omit[node->position-WIDTH] == 0 && 
            node->position-WIDTH != EXIT &&
            node->omit[node->position-WIDTH+1] == 0 && 
            node->position-WIDTH+1 != EXIT &&
            node->omit[node->position] == 1 &&
            node->omit[node->position+1] == 1 &&
            node->omit[node->position+2-WIDTH] == 1 &&
            node->omit[node->position-WIDTH-WIDTH] == 1 &&
            node->omit[node->position-WIDTH-WIDTH+1] == 1){
            return 1;
        }   
    }
    return 0;
}

int floodfill(struct LLNode* node, int* map, int start, int end){
    if(start == end){
        return 1;
    }
    int found = 0;
    map[start] = 1;
    switch(ROOM[start].type)
    {
         case TOPLEFTCORNER:
             if(node->omit[start+1] == 0 && map[start+1] != 1){
                 found = floodfill(node, map, start+1, end);
             }
             if(node->omit[start+WIDTH] == 0 && found == 0 && map[start+WIDTH] != 1){
                 found = floodfill(node, map, start+WIDTH, end);
             }
         break;
    //         
         case TOPEDGE:
             if(node->omit[start-1] == 0 && map[start-1] != 1){
                 found = floodfill(node, map, start-1, end);
             }
             if(node->omit[start+1] == 0 && map[start+1] != 1 && found == 0){
                 found = floodfill(node, map, start+1, end);
             }
             if(node->omit[start+WIDTH] == 0 && map[start+WIDTH] != 1 && found == 0){
                 found = floodfill(node, map, start+WIDTH, end);
             }
             break;
    // 
        case BOTTOMEDGE:
            if(node->omit[start-1] == 0 && map[start-1] != 1){
                found = floodfill(node, map, start-1, end);
            }
            if(node->omit[start-WIDTH] == 0 && map[start-WIDTH] != 1 && found == 0){
                found = floodfill(node, map, start-WIDTH, end);
            }
            if(node->omit[start+1] == 0 && map[start+1] != 1 && found == 0){
                found = floodfill(node, map, start+1, end);
            }
            break;
    
        case LEFTEDGE:
            if(node->omit[start-WIDTH] == 0  && map[start-WIDTH] != 1){
                found = floodfill(node, map, start-WIDTH, end);
            }
            if(node->omit[start+1] == 0  && map[start+1] != 1 && found == 0){
                found = floodfill(node, map, start+1, end);
            }
            if(node->omit[start+WIDTH] == 0 && map[start+WIDTH] != 1 && found == 0){
                found = floodfill(node, map, start+WIDTH, end);
            }            
            break;
            
        case RIGHTEDGE:
            if(node->omit[start-WIDTH] == 0 && map[start-WIDTH] != 1){
                found = floodfill(node, map, start-WIDTH, end);
            }
            if(node->omit[start+WIDTH] == 0 && map[start+WIDTH] != 1 && found == 0){
                found = floodfill(node, map, start+WIDTH, end);
            }
            if(node->omit[start-1] == 0 && map[start-1] != 1 && found == 0){
                found = floodfill(node, map, start-1, end);
            }
            break;
            
        case TOPRIGHTCORNER:
            if(node->omit[start+WIDTH] == 0 && map[start+WIDTH] != 1){
                found = floodfill(node, map, start+WIDTH, end);
            }
            if(node->omit[start-1] == 0 && map[start-1] != 1 && found == 0){
                found = floodfill(node, map, start-1, end);
            }
            break;
    
        case BOTTOMLEFTCORNER:
            if(node->omit[start-WIDTH] == 0 && map[start-WIDTH] != 1){
                found = floodfill(node, map, start-WIDTH, end);
            }
            if(node->omit[start+1] == 0 && map[start+1] != 1 && found == 0){
                found = floodfill(node, map, start+1, end);
            }
            break;
    
        case BOTTOMRIGHTCORNER:
            if(node->omit[start-WIDTH] == 0 && map[start-WIDTH] != 1){
                found = floodfill(node, map, start-WIDTH, end);
            }
            if(node->omit[start-1] == 0 && map[start-1] != 1 && found == 0){
                found = floodfill(node, map, start-1, end);
            }
            break;
    
        case FOURWAY:
            if(node->omit[start-WIDTH] == 0 && map[start-WIDTH] != 1){
                found = floodfill(node, map, start-WIDTH, end);
            }
            if(node->omit[start+1] == 0 && map[start+1] != 1 && found == 0){
                found = floodfill(node, map, start+1, end);
            }
            if(node->omit[start+WIDTH] == 0 && map[start+WIDTH] != 1 && found == 0){
                found = floodfill(node, map, start+WIDTH, end);
            }
            if(node->omit[start-1] == 0 && map[start-1] != 1 && found == 0){
                found = floodfill(node, map, start-1, end);
            }
            break;
    }
    return found;
}

int search_path(struct Node* room, struct LLNode* node) {
    if(node->position == EXIT && node->path_count == GLOBAL_PROPERTIES.max_path_length){
        return 1;
    }
    
    switch(room[EXIT].type)
    {
        case TOPLEFTCORNER:
            if(node->omit[EXIT+1] == 1 && node->omit[EXIT+WIDTH] == 1){
                return 0;
            }
            break;
            
        case TOPEDGE:
            if(node->omit[EXIT-1] == 1 && node->omit[EXIT+1] == 1 && node->omit[EXIT+WIDTH] == 1){
                return 0;
            }
            break;
        
        case BOTTOMEDGE:
            if(node->omit[EXIT-1] == 1 && node->omit[EXIT-WIDTH] == 1 && node->omit[EXIT+1] == 1){
                return 0;
            }
            break;
            
        case LEFTEDGE:
            if(node->omit[EXIT-WIDTH] == 1 && node->omit[EXIT+1] == 1 && node->omit[EXIT+WIDTH] == 1){
                return 0;
            }
            break;
            
        case RIGHTEDGE:
            if(node->omit[EXIT-1] == 1 && node->omit[EXIT-WIDTH] == 1 && node->omit[EXIT+WIDTH] == 1){
                return 0;
            }
            break;
            
        case TOPRIGHTCORNER:
            if(node->omit[EXIT-1] == 1 && node->omit[EXIT+WIDTH] == 1){
                return 0;
            }
            break;
    
        case BOTTOMLEFTCORNER:
            if(node->omit[EXIT-WIDTH] == 1 && node->omit[EXIT+1] == 1){
                return 0;
            }
            break;
    
        case BOTTOMRIGHTCORNER:
            if(node->omit[EXIT-1] == 1 && node->omit[EXIT-WIDTH] == 1){
                return 0;
            }
            break;

        case FOURWAY:
            if(node->omit[EXIT-1] == 1 && node->omit[EXIT-WIDTH] == 1 && node->omit[EXIT+1] == 1 && node->omit[EXIT+WIDTH] == 1){
                return 0;
            }
            break;
    }
    
    
    node->omit[node->position] = 1;
    node->segment_x[room[node->position].x] = 1;
    node->segment_y[room[node->position].y] = 1;
    node->segment_x_path[room[node->position].x] = node->position;
    node->segment_y_path[room[node->position].y] = node->position;
    node->path_count = node->path_count +1;
    
    if(WIDTH > 4 && HEIGHT > 4){
        if(left_u_pitcheck(node) == 1){
            return 0;
        }
        if(right_u_pitcheck(node) == 1){
            return 0;
        }
        if(left_a_pitcheck(node) == 1){
            return 0;
        }
        if(right_a_pitcheck(node) == 1){
            return 0;
        }
        if(top_c_pitcheck(node) == 1){
            return 0;
        }
        if(bottom_c_pitcheck(node) == 1){
            return 0;
        }
        if(top_d_pitcheck(node) == 1){
            return 0;
        }
        if(bottom_d_pitcheck(node) == 1){
            return 0;
        }
    }
    
    int leftcount = 0;
    int rightcount = 0;
    int topcount = 0;
    int bottomcount = 0;
    switch(room[node->position].type)
    {
        case TOPLEFTCORNER:
            VERTICAL_SEGMENT_DETECT
            HORIZONTAL_SEGMENT_DETECT
            PROCESS_NEIGHBOUR(node->position+1, rightcount)
            PROCESS_NEIGHBOUR(node->position+WIDTH, bottomcount)
            break;
            
        case TOPEDGE:    
            VERTICAL_SEGMENT_DETECT
            PROCESS_NEIGHBOUR(node->position-1, leftcount)
            PROCESS_NEIGHBOUR(node->position+1, rightcount)
            PROCESS_NEIGHBOUR(node->position+WIDTH, bottomcount)
            break;
            
        case BOTTOMEDGE:
            VERTICAL_SEGMENT_DETECT
            PROCESS_NEIGHBOUR(node->position-1, leftcount)
            PROCESS_NEIGHBOUR(node->position-WIDTH, topcount)
            PROCESS_NEIGHBOUR(node->position+1, rightcount)
            break;
            
        case LEFTEDGE:
            HORIZONTAL_SEGMENT_DETECT
            PROCESS_NEIGHBOUR(node->position-WIDTH, topcount)
            PROCESS_NEIGHBOUR(node->position+1, rightcount)
            PROCESS_NEIGHBOUR(node->position+WIDTH, bottomcount)
            break;
            
        case RIGHTEDGE:
            HORIZONTAL_SEGMENT_DETECT
            PROCESS_NEIGHBOUR(node->position-1, leftcount)
            PROCESS_NEIGHBOUR(node->position-WIDTH, topcount)
            PROCESS_NEIGHBOUR(node->position+WIDTH, bottomcount)
            break;
        
        case TOPRIGHTCORNER:
            VERTICAL_SEGMENT_DETECT
            HORIZONTAL_SEGMENT_DETECT
            PROCESS_NEIGHBOUR(node->position-1, leftcount)
            PROCESS_NEIGHBOUR(node->position+WIDTH, bottomcount)
            break;
        
        case BOTTOMLEFTCORNER:
            VERTICAL_SEGMENT_DETECT
            HORIZONTAL_SEGMENT_DETECT
            PROCESS_NEIGHBOUR(node->position-WIDTH, topcount)
            PROCESS_NEIGHBOUR(node->position+1, rightcount)
            break;
        
        case BOTTOMRIGHTCORNER:
            VERTICAL_SEGMENT_DETECT
            HORIZONTAL_SEGMENT_DETECT
            PROCESS_NEIGHBOUR(node->position-1, leftcount)
            PROCESS_NEIGHBOUR(node->position-WIDTH, topcount)
            break;
            
        case FOURWAY:
            node->edge_broken = 1;
            PROCESS_NEIGHBOUR(node->position-1, leftcount)
            PROCESS_NEIGHBOUR(node->position-WIDTH, topcount)
            PROCESS_NEIGHBOUR(node->position+1, rightcount)
            PROCESS_NEIGHBOUR(node->position+WIDTH, bottomcount)
             break;
    }    
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
    ROOM = room;
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
        }
        if(n == 3){
            if(GLOBAL_PROPERTIES.end == -1){
                GLOBAL_PROPERTIES.end = count;
            } else {
                printf("You can only have 1 ac unit\n");
                exit(1);
            }
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
    
    struct LLNode* node = new_llnode();
    node->position = GLOBAL_PROPERTIES.start;
    memcpy(node->omit, omit_list,sizeof(uchar)*ROOMSIZE);
     
    int total_paths = search_path(room, node);
    printf("%i\n", total_paths);
    DESTROY_LLNODE(node);
    return 0;
}
