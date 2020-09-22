#include <stdio.h>
#include <string.h>
#include "structs.h"


int main() {
    files_init();
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    int FILE_IO = 1;
    printf("FILE_IO = ");
    scanf("%d", &FILE_IO);
    FILE *in = (FILE_IO ? fin : stdin);
    FILE *out = (FILE_IO ? fout : stdout);
    help(out);
    char cmd[30];
    int exit = 0;
    while (!exit) {
        fscanf(in, "%s", cmd);
        if (FILE_IO)
            fprintf(out, "%s\n", cmd);
        if (strcmp(cmd, "insertm") == 0) {

            Student student;

            fprintf(out, "Enter number of gradebook:\n");
            fscanf(in, "%d", &(student.gradebook_num));
            if (FILE_IO)
                fprintf(out, "%d\n", student.gradebook_num);
            if (is_key(student.gradebook_num)) {
                fprintf(out, "Student with %d gradebook is already exist\n\n", student.gradebook_num);
                continue;
            }
            fprintf(out, "Enter first name:\n");
            fscanf(in, "%s", student.first_name);
            if (FILE_IO)
                fprintf(out, "%s\n", student.first_name);

            fprintf(out, "Enter last name:\n");
            fscanf(in, "%s", student.last_name);
            if (FILE_IO)
                fprintf(out, "%s\n", student.last_name);

            fprintf(out, "Enter admission date year:\n");
            fscanf(in, "%d", &(student.admission_date.year));
            if (FILE_IO)
                fprintf(out, "%d\n", student.admission_date.year);

            fprintf(out, "Enter admission date month:\n");
            fscanf(in, "%d", &(student.admission_date.month));
            if (FILE_IO)
                fprintf(out, "%d\n", student.admission_date.month);

            fprintf(out, "Enter admission date day:\n");
            fscanf(in, "%d", &(student.admission_date.day));
            if (FILE_IO)
                fprintf(out, "%d\n", student.admission_date.day);

            fprintf(out, "Enter faculty:\n");
            fscanf(in, "%s", student.faculty);
            if (FILE_IO)
                fprintf(out, "%s\n", student.faculty);

            fprintf(out, "Enter specialty:\n");
            fscanf(in, "%s", student.specialty);
            if (FILE_IO)
                fprintf(out, "%s\n", student.specialty);

            fprintf(out, "Enter number of course:\n");
            fscanf(in, "%d", &(student.course));
            if (FILE_IO)
                fprintf(out, "%d\n", student.course);

            fprintf(out, "Enter group:\n");
            fscanf(in, "%s", student.group);
            if (FILE_IO)
                fprintf(out, "%s\n", student.group);

            student.first_progress_pos = -5;
            insert_student(student);
            fprintf(out, "Success\n\n");
        } else if (strcmp(cmd, "inserts") == 0) {
            Progress progress;
            int key;

            fprintf(out, "Enter number of gradebook:\n");
            fscanf(in, "%d", &(key));
            if (FILE_IO)
                fprintf(out, "%d\n", key);

            if (!is_key(key)) {
                fprintf(out, "Student with %d gradebook doesn't exist\n\n", key);
                continue;
            }

            fprintf(out, "Enter subject:\n");
            fscanf(in, "%s", progress.subject);
            if (FILE_IO)
                fprintf(out, "%s\n", progress.subject);

            fprintf(out, "Enter term:\n");
            fscanf(in, "%d", &(progress.term_num));
            if (FILE_IO)
                fprintf(out, "%d\n", progress.term_num);

            fprintf(out, "Enter mark:\n");
            fscanf(in, "%d", &(progress.mark));
            if (FILE_IO)
                fprintf(out, "%d\n", progress.mark);

            fprintf(out, "Enter exam date year:\n");
            fscanf(in, "%d", &(progress.exam_date.year));
            if (FILE_IO)
                fprintf(out, "%d\n", progress.exam_date.year);

            fprintf(out, "Enter exam date month:\n");
            fscanf(in, "%d", &(progress.exam_date.month));
            if (FILE_IO)
                fprintf(out, "%d\n", progress.exam_date.month);

            fprintf(out, "Enter exam date day:\n");
            fscanf(in, "%d", &(progress.exam_date.day));
            if (FILE_IO)
                fprintf(out, "%d\n", progress.exam_date.day);

            fprintf(out, "Enter teacher last name:\n");
            fscanf(in, "%s", progress.teacher_last_name);
            if (FILE_IO)
                fprintf(out, "%s\n", progress.teacher_last_name);

            progress.next_progress_pos = -5;
            insert_progr_by_key(key, progress);
            fprintf(out, "Success\n\n");
        } else if (strcmp(cmd, "getm") == 0) {
            int key;
            fprintf(out, "Enter number of gradebook:\n");
            fscanf(in, "%d", &key);
            if (FILE_IO)
                fprintf(out, "%d\n", key);
            if (is_key(key)) {
                print_stud(out, get_stud_by_key(key));
                fprintf(out, "\n");
            } else {
                fprintf(out, "Student with %d gradebook doesn't exist\n\n", key);
            }
        } else if (strcmp(cmd, "delm") == 0) {
            int key;
            fprintf(out, "Enter number of gradebook:\n");
            fscanf(in, "%d", &key);
            if (FILE_IO)
                fprintf(out, "%d\n", key);
            if (is_key(key)) {
                del_stud_by_key(key);
                fprintf(out, "Success\n\n");
            } else {
                fprintf(out, "Student with %d gradebook doesn't exist\n\n", key);
            }
        } else if (strcmp(cmd, "updatem") == 0) {
            int key;
            fprintf(out, "Enter number of gradebook:\n");
            fscanf(in, "%d", &key);
            if (FILE_IO)
                fprintf(out, "%d\n", key);
            if (!is_key(key)) {
                fprintf(out, "Student with %d gradebook doesn't exist\n\n", key);
                continue;
            }
            Student stud = get_stud_by_key(key);
            fprintf(out, "1.First name\n");
            fprintf(out, "2.Last name\n");
            fprintf(out, "3.Admission date\n");
            fprintf(out, "4.Faculty\n");
            fprintf(out, "5.Specialty\n");
            fprintf(out, "6.Course\n");
            fprintf(out, "7.Group\n");
            fprintf(out, "Enter number, what you want to change:\n");
            int num;
            fscanf(in, "%d", &num);
            if (FILE_IO)
                fprintf(out, "%d\n", num);
            if (num == 1) {
                fprintf(out, "Enter new first name:\n");
                fscanf(in, "%s", stud.first_name);
                if (FILE_IO)
                    fprintf(out, "%s\n", stud.first_name);
            } else if (num == 2) {
                fprintf(out, "Enter new last name:\n");
                fscanf(in, "%s", stud.last_name);
                if (FILE_IO)
                    fprintf(out, "%s\n", stud.last_name);
            } else if (num == 3) {
                fprintf(out, "Enter new admission date:\n");
                fprintf(out, "year:\n");
                fscanf(in, "%d", &(stud.admission_date.year));
                if (FILE_IO)
                    fprintf(out, "%d\n", stud.admission_date.year);
                fprintf(out, "month:\n");
                fscanf(in, "%d", &(stud.admission_date.month));
                if (FILE_IO)
                    fprintf(out, "%d\n", stud.admission_date.month);
                fprintf(out, "day:\n");
                fscanf(in, "%d", &(stud.admission_date.day));
                if (FILE_IO)
                    fprintf(out, "%d\n", stud.admission_date.day);
            } else if (num == 4) {
                fprintf(out, "Enter new faculty:\n");
                fscanf(in, "%s", stud.faculty);
                if (FILE_IO)
                    fprintf(out, "%s\n", stud.faculty);
            } else if (num == 5) {
                fprintf(out, "Enter new specialty:\n");
                fscanf(in, "%s", stud.specialty);
                if (FILE_IO)
                    fprintf(out, "%s\n", stud.specialty);
            } else if (num == 6) {
                fprintf(out, "Enter new course:\n");
                fscanf(in, "%d", &(stud.course));
                if (FILE_IO)
                    fprintf(out, "%d\n", stud.course);
            } else if (num == 7) {
                fprintf(out, "Enter new group:\n");
                fscanf(in, "%s", stud.group);
                if (FILE_IO)
                    fprintf(out, "%s\n", stud.group);
            } else {
                fprintf(out, "Incorrect number, try again\n");
                continue;
            }
            edit_stud_by_pos(get_ind_by_key(key).pos, stud);
            fprintf(out, "Success\n\n");
        } else if (strcmp(cmd, "updates") == 0) {
            int key;
            fprintf(out, "Enter number of gradebook:\n");
            fscanf(in, "%d", &key);
            if (FILE_IO)
                fprintf(out, "%d\n", key);
            if (!is_key(key)) {
                fprintf(out, "Student with %d gradebook doesn't exist\n\n", key);
                continue;
            }

            char subj[30];
            fprintf(out, "Enter subject:\n");
            fscanf(in, "%s", subj);
            if (FILE_IO)
                fprintf(out, "%s\n", subj);

            int term;
            fprintf(out, "Enter term:\n");
            fscanf(in, "%d", &term);
            if (FILE_IO)
                fprintf(out, "%d\n", term);

            int pos = get_progr_pos(key, subj, term);
            if (pos == INVALID_PROGR_MARK) {
                fprintf(out, "This progress doesn't exist\n\n");
                continue;
            }
            Progress progr = get_progr_by_pos(pos);
            fprintf(out, "1.Mark\n");
            fprintf(out, "2.Exam date\n");
            fprintf(out, "3.Teacher\n");
            int num;
            fscanf(in, "%d", &num);
            if (FILE_IO)
                fprintf(out, "%d\n", num);
            if (num == 1) {
                fprintf(out, "Enter new mark:\n");
                fscanf(in, "%d", &(progr.mark));
                if (FILE_IO)
                    fprintf(out, "%d\n", progr.mark);
            } else if (num == 2) {
                fprintf(out, "Enter new exam date:\n");
                fprintf(out, "year:\n");
                fscanf(in, "%d", &(progr.exam_date.year));
                if (FILE_IO)
                    fprintf(out, "%d\n", progr.exam_date.year);
                fprintf(out, "month:\n");
                fscanf(in, "%d", &(progr.exam_date.month));
                if (FILE_IO)
                    fprintf(out, "%d\n", progr.exam_date.month);
                fprintf(out, "day:\n");
                fscanf(in, "%d", &(progr.exam_date.day));
                if (FILE_IO)
                    fprintf(out, "%d\n", progr.exam_date.day);
            } else if (num == 3) {
                fprintf(out, "Enter new teacher last name:\n");
                fscanf(in, "%s", progr.teacher_last_name);
                if (FILE_IO)
                    fprintf(out, "%s\n", progr.teacher_last_name);
            } else {
                fprintf(out, "Incorrect number, try again\n");
                continue;
            }
            edit_progr_by_pos(pos, progr);
            fprintf(out, "Success\n\n");
        } else if (strcmp(cmd, "gets") == 0) {
            int key;
            fprintf(out, "Enter number of gradebook:\n");
            fscanf(in, "%d", &key);
            if (FILE_IO)
                fprintf(out, "%d\n", key);
            if (!is_key(key)) {
                fprintf(out, "Student with %d gradebook doesn't exist\n\n", key);
                continue;
            }

            char subj[30];
            fprintf(out, "Enter subject:\n");
            fscanf(in, "%s", subj);
            if (FILE_IO)
                fprintf(out, "%s\n", subj);

            int term;
            fprintf(out, "Enter term:\n");
            fscanf(in, "%d", &term);
            if (FILE_IO)
                fprintf(out, "%d\n", term);

            Progress progr = get_progr_by_args(key, subj, term);
            if (progr.mark == INVALID_PROGR_MARK) {
                fprintf(out, "This progress doesn't exist\n\n");
                continue;
            }

            print_stud(out, get_stud_by_key(key));
            print_progr(out, progr);
            fprintf(out, "\n");
        } else if (strcmp(cmd, "dels") == 0) {
            int key;
            fprintf(out, "Enter number of gradebook:\n");
            fscanf(in, "%d", &key);
            if (FILE_IO)
                fprintf(out, "%d\n", key);
            if (!is_key(key)) {
                fprintf(out, "Student with %d gradebook doesn't exist\n\n", key);
                continue;
            }

            char subj[30];
            fprintf(out, "Enter subject:\n");
            fscanf(in, "%s", subj);
            if (FILE_IO)
                fprintf(out, "%s\n", subj);

            int term;
            fprintf(out, "Enter term:\n");
            fscanf(in, "%d", &term);
            if (FILE_IO)
                fprintf(out, "%d\n", term);

            int pos = get_progr_pos(key, subj, term);
            if (pos == INVALID_PROGR_MARK) {
                fprintf(out, "This progress doesn't exist\n\n");
                continue;
            }

            del_progr_by_args(key, subj, term);
            fprintf(out, "Success\n\n");
        } else if (strcmp(cmd, "dump") == 0) {
            dump(out);
        } else if (strcmp(cmd, "exit") == 0) {
            exit = 1;
            continue;
        }
    }
    fclose(fin);
    fclose(fout);
    return 0;
}
