#ifndef LAB_1_STRUCTS_H
#define LAB_1_STRUCTS_H

struct DateStruct {
    int year;
    int month;
    int day;
};

typedef struct DateStruct Date;

struct StudentStruct {
    int gradebook_num;
    char first_name[30];
    char last_name[30];
    Date admission_date;
    char faculty[30];
    char specialty[30];
    int course;
    char group[30];
    int first_progress_pos;
};

struct ProgressStruct {
    int term_num;
    char subject[30];
    int mark;
    Date exam_date;
    char teacher_last_name[30];
    int next_progress_pos;
};

struct IndexStruct {
    int key;
    int pos;
};

typedef struct StudentStruct Student;
typedef struct ProgressStruct Progress;
typedef struct IndexStruct Index;

#define IND_SIZ  sizeof(Index)
#define STUD_SIZ  sizeof(Student)
#define PROGR_SIZ  sizeof(Progress)
#define INVALID_PROGR_MARK -100

int num_of_inds();
Index get_ind_by_pos(int pos);
Index get_ind_by_key(int key);
int is_key(int key);
int ind_pos_by_key(int key);
Student get_stud_by_pos(int pos);
Student get_stud_by_key(int key);
Progress get_progr_by_pos(int pos);
Progress get_progr_by_args(int key, const char *subj, int term);
void edit_stud_by_pos(int pos, Student stud);
void edit_ind_by_pos(int pos, Index ind);
void edit_progr_by_pos(int pos, Progress p);
void del_progr_by_args(int key, const char *subj, int term);
void del_all_progr_by_key(int key);
int del_stud_by_key(int key);
int insert_index(Index ind);
int insert_student(Student stud);
int num_of_progr();
int insert_progr_by_key(int key, Progress progr);
void files_init();
void help(FILE* out);
void dump(FILE* out);
void print_stud(FILE *out,Student stud);
void print_progr(FILE *out,Progress progr);
int get_progr_pos(int key, const char *subj, int term);
int progr_num_by_key(int key);


#endif //LAB_1_STRUCTS_H
