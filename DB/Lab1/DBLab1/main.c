// 1-n identifying relationship with AI(auto increment) keys
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//const int MAX_NUMBER_OF_USERS = 1e6;
//const int MAX_NUMBER_OF_ORDERS = 1e9;
struct Date {
    int day, month, year;
};
struct User {
    int id;
    char phone_number[16];
    char name[60];
    char password[45];
    int first_order_id;
    char is_deleted;
    int offset;
};
void print_User(struct User user, char is_ut) {
    if (user.id == -1) {
        printf("No match for this key\n");
        return;
    }
    if (user.is_deleted == 1) {
        if (is_ut) printf("Deleted\n");
        else printf("No match for this key\n");
        return;
    }
    printf("id = %d\nphone_number = %s\nname = %s\npassword = %s\n", user.id, user.phone_number, user.name, user.password);
    if(is_ut) {
        printf("first_order_id = %d\noffset = %d\n",  user.first_order_id, user.offset);
    }
}
void read_User(struct User *user_ptr) {
    printf("Phone number: ");
    scanf("%s", user_ptr->phone_number);
    printf("Name and surname: ");
    char surname[21];
    surname[0] = ' ';
    scanf("%s %s", user_ptr->name, surname+1);
    strncat(user_ptr->name, surname, 20);
    printf("Password: ");
    scanf("%s", user_ptr->password);
}
struct Order {
    int id;
    int user_id;
    float cost;
    struct Date date;
    char is_deleted;
    int offset;
    int next_order_id;
    int prev_order_id;
};
void print_Order(struct Order order, char is_ut) {
    if (order.id == -1) {
        printf("No match for this key\n");
        return;
    };
    if (order.is_deleted == 1) {
        if (is_ut) printf("Deleted\n");
        else printf("No match for this key\n");
        return;
    }
    printf("id = %d\nUser id = %d\ncost = %f\ndate = %d.%d.%d\n", order.id, order.user_id, order.cost, order.date.day, order.date.month, order.date.year);
    if (is_ut) {
        printf("next_order_id = %d\nprev_order_id = %d\noffset = %d\n", order.next_order_id, order.prev_order_id, order.offset);
    }
}
void read_Order(struct Order *order_ptr, char is_update) {
    if (!is_update) {
        printf("User id: ");
        scanf("%d", &order_ptr->user_id);
    }
    printf("Cost: ");
    scanf("%f", &order_ptr->cost);
    printf("Date: ");
    scanf("%d.%d.%d", &order_ptr->date.day, &order_ptr->date.month, &order_ptr->date.year);
}
struct Index {
    int key;
    int offset; // in file offset*sizeof(struct)
    char is_deleted;
};
struct StackNode {
    int data;
    struct StackNode *next;
};
char is_stack_empty(struct StackNode *top) {
    return top == NULL;
}
void push(struct StackNode **top_ptr, int value) {
    struct StackNode* new_node = (struct StackNode*) malloc(sizeof(struct StackNode));
    new_node->data = value;
    new_node->next = *top_ptr;
    *top_ptr = new_node;
}
void pop(struct StackNode **top_ptr) {
    if (is_stack_empty(*top_ptr)) {
        return;
    }
    struct StackNode *temp = *top_ptr;
    *top_ptr = temp->next;
    free(temp);
}
void read_in_stack_from_file(FILE *file, struct StackNode **stack_ptr) {
    int temp;
    while(fread(&temp, sizeof(int), 1, file) == 1) {
        push(stack_ptr, temp);
    }
}
void write_from_stack_to_file(FILE *file, struct StackNode **stack_ptr) {
    while(*stack_ptr != NULL) {
        fwrite(*stack_ptr, sizeof(struct StackNode), 1, file);
        *stack_ptr = (*stack_ptr)->next;
    }
}
void init(FILE **master_fl_ptr, FILE **master_ind_ptr, FILE **slave_fl_ptr, FILE **slave_ind_ptr, struct StackNode **master_garbage_stack_ptr,
          struct StackNode **slave_garbage_stack_ptr) {

    // data and index files
    *master_fl_ptr = fopen("user.fl", "rb+");
    if (*master_fl_ptr == NULL) {
        *master_fl_ptr = fopen("user.fl", "wb+");
    }
    *master_ind_ptr = fopen("user.ind", "rb+");
    if (*master_ind_ptr == NULL) {
        *master_ind_ptr = fopen("user.ind", "wb+");
    }
    *slave_fl_ptr = fopen("order.fl", "rb+");
    if (*slave_fl_ptr == NULL) {
        *slave_fl_ptr = fopen("order.fl", "wb+");
    }
    *slave_ind_ptr = fopen("order.ind", "rb+");
    if (*slave_ind_ptr == NULL) {
        *slave_ind_ptr = fopen("order.ind", "wb+");
    }

    // garbage files
    FILE *master_garb_file, *slave_garb_file;

    // master garbage file
    master_garb_file = fopen("user.garb", "rb");
    if (master_garb_file == NULL) {
        master_garb_file = fopen("user.garb", "wb");
    }
    else {
        read_in_stack_from_file(master_garb_file, master_garbage_stack_ptr);
    }
    fclose(master_garb_file);

    // slave garbage file
    slave_garb_file = fopen("order.garb", "rb");
    if (slave_garb_file == NULL) {
        slave_garb_file = fopen("order.garb", "wb");
    }
    else {
        read_in_stack_from_file(slave_garb_file, slave_garbage_stack_ptr);
    }
    fclose(slave_garb_file);
}



struct User get_master(FILE *master_fl, FILE *master_ind, int key) {
    struct User return_value;
    struct Index index_info;
    return_value.id = -1;
    if (key < 1) {
        printf("Wrong key - %d\n", key);
    }
    else if(fseek(master_ind, (key-1)*sizeof(struct Index), SEEK_SET) != 0) {
        //printf("No match for this key\n");
    }
    else if (fread(&index_info, sizeof(struct Index), 1, master_ind) != 1) {
        //printf("No match for this key\n");
    }
    else if (fseek(master_fl, index_info.offset*sizeof(struct User), SEEK_SET) != 0) {
        //printf("No match for this key\n");
    }
    else if (fread(&return_value, sizeof(struct User), 1, master_fl) != 1) {
        //printf("No match for this key\n");
        return_value.id = -1;
    }
    else if (index_info.is_deleted && !return_value.is_deleted) {
        return_value.id = -1;
    }
    return return_value;
}

void rewrite_master(FILE *master_fl, FILE* master_ind, int key, int new_key, struct User new_data/*, char is_delete*/) { // if key == new_key - update
    struct User old_data;
    //if (key != new_key) {
        old_data = get_master(master_fl, master_ind, key);
   // }
   /* else {
        old_data.offset = new_data.offset;
        old_data.first_order_id = new_data.first_order_id;
        old_data.is_deleted = new_data.is_deleted;
    }*/
    new_data.offset = old_data.offset;
    new_data.id = new_key;
    if (key == new_key) {
        new_data.is_deleted = old_data.is_deleted;
        new_data.first_order_id = old_data.first_order_id;
    }
    fseek(master_fl, new_data.offset * sizeof(struct User), SEEK_SET);
    fwrite(&new_data, sizeof(struct User), 1, master_fl);
    if (key != new_key) {
        fseek(master_ind, 0, SEEK_END);
        struct Index new_index;
        new_index.offset = new_data.offset;
        new_index.key = new_data.id;
        new_index.is_deleted = 0;
        fwrite(&new_index, sizeof(struct Index), 1, master_ind);
    }
}

void update_master(FILE *master_fl, FILE* master_ind, int key, int new_key, struct User new_data) {
    // using if and rewrite
}

void insert_master(FILE *master_fl, FILE* master_ind, struct StackNode **master_garbage_stack_ptr, int *prev_key_ptr, struct User data) {
    // finding offset and key of prev
    int offset = 0;
    struct User prev;
    if (fseek(master_fl, -sizeof(struct User), SEEK_END) == 0) {
        fread(&prev, sizeof(struct User), 1, master_fl);
        offset = prev.offset + 1;
        if (*prev_key_ptr == -1) {
            *prev_key_ptr = prev.id;
        }
    }
    else
        *prev_key_ptr = 0;
    data.is_deleted = 0;
    data.first_order_id = -1;
    data.id = *prev_key_ptr + 1;
    if (!is_stack_empty(*master_garbage_stack_ptr)) { // rewrite
        int key = (*master_garbage_stack_ptr)->data;
        pop(master_garbage_stack_ptr);
        rewrite_master(master_fl, master_ind, key, data.id, data);
    }
    else {
        data.offset = offset;

        fseek(master_fl, 0, SEEK_END);
        fwrite(&data, sizeof(struct User), 1, master_fl);
        struct Index data_index;
        data_index.offset = offset;
        data_index.key = data.id;
        data_index.is_deleted = 0;
        fseek(master_ind, 0, SEEK_END);
        fwrite(&data_index, sizeof(struct Index), 1, master_ind);
    }
    (*prev_key_ptr)++;
    printf("key = %d\n", *prev_key_ptr);
}

struct Order get_slave(FILE *slave_fl, FILE *slave_ind, int key) {
    struct Order return_value;
    struct Index index_info;
    return_value.id = -1;
    if (key < 1) {
        printf("Wrong key - %d\n", key);
    }
    else if (fseek(slave_ind, (key-1)*sizeof(struct Index), SEEK_SET) != 0) {
        //printf("No match for this key\n");
    }
    else if (fread(&index_info, sizeof(struct Index), 1, slave_ind) != 1) {
        //printf("No match for this key\n");
    }
    else if (fseek(slave_fl, index_info.offset*sizeof(struct Order), SEEK_SET) != 0) {
        //printf("No match for this key\n");
    }
    else if (fread(&return_value, sizeof(struct Order), 1, slave_fl) != 1) {
        //printf("No match for this key\n");
        return_value.id = -1;
    }
    else if (index_info.is_deleted && !return_value.is_deleted) {
        return_value.id = -1;
    }
    return return_value;
}

void rewrite_slave(FILE *slave_fl, FILE* slave_ind, int key, int new_key, struct Order new_data/*, char is_delete*/) { // if key == new_key - update
    struct Order old_data;
    //if (key != new_key) {
        old_data = get_slave(slave_fl, slave_ind, key);
    //}
    /*else {
        old_data = new_data;
        old_data.offset = new_data.offset;
        old_data.next_order_id = new_data.next_order_id;
        old_data.prev_order_id = new_data.prev_order_id;
        old_data.is_deleted = new_data.is_deleted;
    }*/
    new_data.offset = old_data.offset;
    new_data.id = new_key;
    if (key == new_key) {
        new_data.is_deleted = old_data.is_deleted;
        new_data.next_order_id = old_data.next_order_id;
        new_data.prev_order_id = old_data.prev_order_id;
    }
    fseek(slave_fl, new_data.offset * sizeof(struct Order), SEEK_SET);
    fwrite(&new_data, sizeof(struct Order), 1, slave_fl);
    if (key != new_key) {
        fseek(slave_ind, 0, SEEK_END);
        struct Index new_index;
        new_index.offset = new_data.offset;
        new_index.key = new_data.id;
        new_index.is_deleted = 0;
        fwrite(&new_index, sizeof(struct Index), 1, slave_ind);
    }
}

void insert_slave(FILE *master_fl, FILE* master_ind, FILE *slave_fl, FILE* slave_ind, struct StackNode **slave_garbage_stack_ptr, int *prev_key_ptr,
        struct Order data) {
    struct User master_data = get_master(master_fl, master_ind, data.user_id);

    // finding offset and key of prev
    int offset = 0;
    struct Order prev;
    if (fseek(slave_fl, -sizeof(struct Order), SEEK_END) == 0) {
        fread(&prev, sizeof(struct Order), 1, slave_fl);
        offset = prev.offset + 1;
        if (*prev_key_ptr == -1) {
            *prev_key_ptr = prev.id;
        }
    }
    else
        *prev_key_ptr = 0;
    data.is_deleted = 0;
    data.next_order_id = master_data.first_order_id;
    data.prev_order_id = -1;
    data.id = *prev_key_ptr + 1;
    if (!is_stack_empty(*slave_garbage_stack_ptr)) { // rewrite
        int key = (*slave_garbage_stack_ptr)->data;
        pop(slave_garbage_stack_ptr);
        rewrite_slave(slave_fl, slave_ind, key, data.id, data);
    }
    else {
        data.offset = offset;
        /*data.is_deleted = 0;
        data.next_order_id = master_data.first_order_id;
        data.prev_order_id = -1;*/
        fseek(slave_fl, 0, SEEK_END);
        fwrite(&data, sizeof(struct Order), 1, slave_fl);
        struct Index data_index;
        data_index.offset = offset;
        data_index.key = data.id;
        data_index.is_deleted = 0;
        fseek(slave_ind, 0, SEEK_END);
        fwrite(&data_index, sizeof(struct Index), 1, slave_ind);
    }
    // updating next_order
    if (master_data.first_order_id != -1) {
        struct Order next_order = get_slave(slave_fl, slave_ind, master_data.first_order_id);
        next_order.prev_order_id = data.id;
        rewrite_slave(slave_fl, slave_ind, next_order.id, next_order.id, next_order);
    }
    // updating master
    master_data.first_order_id = data.id;
    rewrite_master(master_fl, master_ind, data.user_id, data.user_id, master_data);

    (*prev_key_ptr)++;
    printf("key = %d\n", *prev_key_ptr);
    //master_data.first_order_id
}
void print_all_orders_of_user(FILE *master_fl, FILE* master_ind, FILE *slave_fl, FILE* slave_ind, int key) {
    struct User user = get_master(master_fl, master_ind, key);
    if (user.first_order_id == -1) printf("No orders\n");
    else {
        struct Order cur_order = get_slave(slave_fl, slave_ind, user.first_order_id);
        while (1) {
            print_Order(cur_order, 1);
            printf("\n");
            if (cur_order.next_order_id == -1) break;
            cur_order = get_slave(slave_fl, slave_ind, cur_order.next_order_id);
        }
    }
}
void delete_index(FILE* ind, int key) {
    fseek(ind, (key-1)*sizeof(struct Index), SEEK_SET);
    struct Index new_index;
    fread(&new_index, sizeof(struct Index), 1, ind);
    new_index.is_deleted = 1;
    fseek(ind, -sizeof(struct Index), SEEK_CUR);
    fwrite(&new_index, sizeof(struct Index), 1, ind);
}
void delete_slave(FILE *master_fl, FILE* master_ind, FILE *slave_fl, FILE* slave_ind, int *key_ptr, struct StackNode **stack) {
    struct Order this_order = get_slave(slave_fl, slave_ind, *key_ptr);
    if (this_order.id == -1) {
        printf("Wrong key\n");
        return;
    }
    this_order.is_deleted = 1;
    struct Order next_order;
    int next_order_id = -1;
    if (this_order.next_order_id != -1) {
        next_order = get_slave(slave_fl, slave_ind, this_order.next_order_id);
        next_order_id = next_order.id;
    }
    if (this_order.prev_order_id == -1) {
        struct User master = get_master(master_fl, master_ind, this_order.user_id);
        master.first_order_id = next_order_id;
        *key_ptr = next_order_id;
        rewrite_master(master_fl, master_ind, master.id, master.id, master);
        if (next_order_id != -1) next_order.prev_order_id = -1;
    }
    else {
        struct Order prev_order = get_slave(slave_fl, slave_ind, this_order.prev_order_id);
        prev_order.next_order_id = next_order_id;
        rewrite_slave(slave_fl, slave_ind, prev_order.id, prev_order.id, prev_order);
        if (next_order_id != -1) next_order.prev_order_id = prev_order.id;
    }
    if (next_order_id != -1) rewrite_slave(slave_fl, slave_ind, next_order.id, next_order.id, next_order);
    rewrite_slave(slave_fl, slave_ind, this_order.id, this_order.id, this_order);
    push(stack, this_order.id);
    // index del = 1
    delete_index(slave_ind, this_order.id);
}
void delete_master(FILE *master_fl, FILE* master_ind, FILE *slave_fl, FILE* slave_ind, int key, struct StackNode **master_stack,
        struct StackNode **slave_stack) {
    struct User master = get_master(master_fl, master_ind, key);
    if (master.id == -1) {
        printf("Wrong key\n");
        return;
    }
    master.is_deleted = 1;
    while(master.first_order_id != -1) { // delete slaves
        delete_slave(master_fl, master_ind, slave_fl, slave_ind, &master.first_order_id, slave_stack);
    }
    rewrite_master(master_fl, master_ind, master.id, master.id, master);
    push(master_stack, master.id);
    // index del = 1
    delete_index(master_ind, master.id);
}
int number_of_records(FILE* ind) {
    int number = 0;
    fseek(ind, 0, SEEK_SET);
    struct Index cur_index;
    while (fread(&cur_index, sizeof(struct Index), 1, ind) == 1) {
        if (!cur_index.is_deleted) number++;
    }
    return number;
}

int main()
{
    printf("Hi\n");
    FILE *master_fl, *master_ind, *slave_fl, *slave_ind;
    struct StackNode *master_garbage_stack = NULL, *slave_garbage_stack = NULL;
    init(&master_fl, &master_ind, &slave_fl, &slave_ind, &master_garbage_stack, &slave_garbage_stack);
    int prev_master_key_ptr = -1, prev_slave_key_ptr = -1;
    char command[20];
    printf("Enter command: ");
    scanf("%s", command);
    while (strcmp(command,"exit") != 0) {
        if (strcmp(command,"get-m") == 0) {
            printf("Enter key: ");
            int key;
            scanf("%d", &key);
            struct User ans = get_master(master_fl, master_ind, key);
            print_User(ans, 1);
        }
        if (strcmp(command,"get-s") == 0) {
            printf("Enter key: ");
            int key;
            scanf("%d", &key);
            struct Order ans = get_slave(slave_fl, slave_ind, key);
            print_Order(ans, 1);
        }
        if (strcmp(command,"insert-m") == 0) {
            printf("Enter user data:\n");
            struct User input;
            read_User(&input);
            insert_master(master_fl, master_ind, &master_garbage_stack, &prev_master_key_ptr, input);
        }
        if (strcmp(command,"insert-s") == 0) {
            printf("Enter order data:\n");
            struct Order input;
            read_Order(&input, 0);
            insert_slave(master_fl, master_ind, slave_fl, slave_ind, &slave_garbage_stack, &prev_slave_key_ptr, input);
        }
        if (strcmp(command,"update-m") == 0) {
            printf("Enter key: ");
            int key;
            scanf("%d", &key);
            printf("Enter new user data:\n");
            struct User input;
            read_User(&input);
            rewrite_master(master_fl, master_ind, key, key, input);
        }
        if (strcmp(command,"update-s") == 0) {
            printf("Enter key: ");
            int key;
            scanf("%d", &key);
            printf("Enter new order data:\n");
            struct Order input;
            read_Order(&input, 1);
            rewrite_slave(slave_fl, slave_ind, key, key, input);
        }
        if (strcmp(command,"get-all-s-of-m") == 0) {
            printf("Enter user key: ");
            int key;
            scanf("%d", &key);
            print_all_orders_of_user(master_fl, master_ind, slave_fl, slave_ind, key);
        }
        if (strcmp(command,"del-m") == 0) {
            printf("Enter key: ");
            int key;
            scanf("%d", &key);
            delete_master(master_fl, master_ind, slave_fl, slave_ind, key, &master_garbage_stack, &slave_garbage_stack);
        }
        if (strcmp(command,"del-s") == 0) {
            printf("Enter key: ");
            int key;
            scanf("%d", &key);
            delete_slave(master_fl, master_ind, slave_fl, slave_ind, &key, &slave_garbage_stack);
        }
        if (strcmp(command,"num-m") == 0) {
            printf("%d\n", number_of_records(master_ind));
        }
        if (strcmp(command,"num-s") == 0) {
            printf("%d\n", number_of_records(slave_ind));
        }
        printf("Enter command: ");
        scanf("%s", command);
    }

    // updating garbage
    FILE *master_garb_file, *slave_garb_file;
    master_garb_file = fopen("user.garb", "wb");
    write_from_stack_to_file(master_garb_file, &master_garbage_stack);
    fclose(master_garb_file);
    slave_garb_file = fopen("order.garb", "wb");
    write_from_stack_to_file(slave_garb_file, &slave_garbage_stack);
    fclose(slave_garb_file);

    // closing files
    fclose(master_fl);
    fclose(master_ind);
    fclose(slave_fl);
    fclose(slave_ind);

    // free memory
    free(master_garbage_stack);
    free(slave_garbage_stack);
    return 0;
}

