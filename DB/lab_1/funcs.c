#include <stdio.h>
#include <string.h>
#include "structs.h"

int num_of_inds() {
    FILE *f = fopen("S.ind", "rb");
    Index res;
    fread(&res, IND_SIZ, 1, f);
    fclose(f);
    return res.key;
}

Index get_ind_by_pos(int pos) {
    FILE *f = fopen("S.ind", "rb");
    Index res = {-1, -1};
    fseek(f, (pos + 1) * IND_SIZ, SEEK_SET);
    fread(&res, IND_SIZ, 1, f);
    fclose(f);
    return res;
}

Index get_ind_by_key(int key) {
    int l = 0;
    int r = num_of_inds() - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        Index temp = get_ind_by_pos(m);
        if (temp.key == key)
            return temp;
        if (temp.key < key)
            l = m + 1;
        else
            r = m - 1;
    }
    return (Index) {-1, -1};
}

int is_key(int key) {
    Index ind = get_ind_by_key(key);
    return (ind.key > 0 || ind.pos > 0);
}

int ind_pos_by_key(int key) {
    int l = 0;
    int r = num_of_inds() - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        Index temp = get_ind_by_pos(m);
        if (temp.key == key)
            return m;
        if (temp.key < key)
            l = m + 1;
        else
            r = m - 1;
    }
    return -5;
}

Student get_stud_by_pos(int pos) {
    FILE *f = fopen("S.fl", "rb");
    Student res = {-1, "\0", "\0", -1, -1,
                   -1, "\0", "\0", -1, "\0", -1};
    fseek(f, pos * STUD_SIZ, SEEK_SET);
    fread(&res, STUD_SIZ, 1, f);
    fclose(f);
    return res;
}

Student get_stud_by_key(int key) {
    Index ind = get_ind_by_key(key);
    Student res = get_stud_by_pos(ind.pos);
    return res;
}

Progress get_progr_by_pos(int pos) {
    FILE *f = fopen("P.fl", "rb");
    Progress res;
    fseek(f, (pos + 1) * PROGR_SIZ, SEEK_SET);
    fread(&res, PROGR_SIZ, 1, f);
    fclose(f);
    return res;
}

Progress get_progr_by_args(int key, const char *subj, int term) {
    Student student = get_stud_by_key(key);
    Progress cur = get_progr_by_pos(student.first_progress_pos);
    int ret = 1;
    while (cur.term_num != term || strcmp(subj, cur.subject) != 0) {
        if (cur.next_progress_pos > 0)
            cur = get_progr_by_pos(cur.next_progress_pos);
        else {
            ret = 0;
            break;
        }
    }
    if (!ret)
        cur.mark = INVALID_PROGR_MARK;
    return cur;
}

int get_progr_pos(int key, const char *subj, int term){
    Student student = get_stud_by_key(key);
    Progress cur = get_progr_by_pos(student.first_progress_pos);
    int ret = student.first_progress_pos;
    while (cur.term_num != term || strcmp(subj, cur.subject) != 0) {
        if (cur.next_progress_pos > 0){
            ret = cur.next_progress_pos;
            cur = get_progr_by_pos(cur.next_progress_pos);
        }
        else {
            ret = INVALID_PROGR_MARK;
            break;
        }
    }
    return ret;
}

void edit_stud_by_pos(int pos, Student stud) {
    FILE *f = fopen("S.fl", "rb+");
    fseek(f, pos * STUD_SIZ, SEEK_SET);
    fwrite(&stud, STUD_SIZ, 1, f);
    fclose(f);
}

void edit_ind_by_pos(int pos, Index ind) {
    FILE *f = fopen("S.ind", "rb+");
    fseek(f, (pos + 1) * IND_SIZ, SEEK_SET);
    fwrite(&ind, IND_SIZ, 1, f);
    fclose(f);
}

void edit_progr_by_pos(int pos, Progress p) {
    FILE *f = fopen("P.fl", "rb+");
    fseek(f, (pos + 1) * PROGR_SIZ, SEEK_SET);
    fwrite(&p, PROGR_SIZ, 1, f);
    fclose(f);
}


void del_progr_by_args(int key, const char *subj, int term) {
    Student student = get_stud_by_key(key);
    Progress del = get_progr_by_args(key, subj, term);
    int del_pos = student.first_progress_pos;
    int prev_pos = del_pos;
    while (get_progr_by_pos(del_pos).term_num != term || strcmp(subj, get_progr_by_pos(del_pos).subject) != 0) {
        prev_pos = del_pos;
        del_pos = get_progr_by_pos(del_pos).next_progress_pos;
    }
    if (prev_pos != del_pos) {
        Progress prev_progr = get_progr_by_pos(prev_pos);
        prev_progr.next_progress_pos = del.next_progress_pos;
        edit_progr_by_pos(prev_pos, prev_progr);
    } else {
        student.first_progress_pos = del.next_progress_pos;
        edit_stud_by_pos(get_ind_by_key(key).pos, student);
    }

    Progress info = get_progr_by_pos(-1);
    del.next_progress_pos = info.next_progress_pos;
    info.next_progress_pos = del_pos;
    edit_progr_by_pos(del_pos, del);
    edit_progr_by_pos(-1, info);
}

void del_all_progr_by_key(int key) {
    Student stud = get_stud_by_key(key);
    Progress progr = get_progr_by_pos(stud.first_progress_pos);
    Progress info = get_progr_by_pos(-1);
    int empty_pos = info.next_progress_pos;
    info.next_progress_pos = stud.first_progress_pos;
    edit_progr_by_pos(-1, info);
    stud.first_progress_pos = -1;
    edit_stud_by_pos(get_ind_by_key(key).pos, stud);
    int pos = stud.first_progress_pos;
    while (progr.next_progress_pos >= 0) {
        pos = progr.next_progress_pos;
        progr = get_progr_by_pos(progr.next_progress_pos);
    }
    progr.next_progress_pos = empty_pos;
    edit_progr_by_pos(pos, progr);
}

int del_stud_by_key(int key) {
    Index del = get_ind_by_key(key);
    if (del.key != key)
        return 0;
    Student last_stud = get_stud_by_pos(num_of_inds() - 1);
    del_all_progr_by_key(key);
    edit_stud_by_pos(del.pos, last_stud);
    Index last = get_ind_by_key(last_stud.gradebook_num);
    last.pos = del.pos;
    edit_ind_by_pos(ind_pos_by_key(last.key), last);
    Index info = get_ind_by_pos(-1);
    int new_size = --info.key;
    edit_ind_by_pos(-1, info);
    int del_pos = ind_pos_by_key(del.key);
    while (del_pos < new_size) {
        edit_ind_by_pos(del_pos, get_ind_by_pos(del_pos + 1));
        ++del_pos;
    }
    return 1;
}

int insert_index(Index ind) {
    //printf("insert index start\n");
    int l = 0;
    int r = num_of_inds() - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        Index temp = get_ind_by_pos(m);
        if (temp.key == ind.key) {
            break;
        }
        if (temp.key < ind.key)
            l = m + 1;
        else
            r = m - 1;
    }
    if (r > l) {
        //printf("insert index return 0\n");
        return 0;
    }
    int insert_pos = l;
    int cur = num_of_inds();
    while (cur > insert_pos) {
        edit_ind_by_pos(cur, get_ind_by_pos(cur - 1));
        --cur;
    }
    edit_ind_by_pos(cur, ind);
    Index info = get_ind_by_pos(-1);
    ++info.key;
    edit_ind_by_pos(-1, info);
    //printf("insert index return 1\n");
    return 1;
}

int insert_student(Student stud) {
    //printf("insert student start\n");
    Index ind = {stud.gradebook_num, num_of_inds()};
    if (!insert_index(ind)) {
        // printf("insert student return 0\n");
        return 0;
    }
    edit_stud_by_pos(ind.pos, stud);
    //printf("insert student return 1\n");
    return 1;
}

int num_of_progr() {
    FILE *f = fopen("P.fl", "rb");
    Progress info;
    fread(&info, PROGR_SIZ, 1, f);
    fclose(f);
    return info.mark;
}

int insert_progr_by_key(int key, Progress progr) {
    printf("insert progr start\n");
    if (!is_key(key)) {
        printf("insert progr return 0\n");
        return 0;
    }
    Progress prev;
    Student stud = get_stud_by_key(key);
    int prev_pos = stud.first_progress_pos;
    Progress info = get_progr_by_pos(-1);
    int insert_pos = info.next_progress_pos;
    if (stud.first_progress_pos < 0) {
        stud.first_progress_pos = insert_pos;
        edit_stud_by_pos(get_ind_by_key(key).pos, stud);
    } else {
        prev = get_progr_by_pos(stud.first_progress_pos);
        while (prev.next_progress_pos >= 0) {
            prev_pos = prev.next_progress_pos;
            prev = get_progr_by_pos(prev.next_progress_pos);
        }
        prev.next_progress_pos = info.next_progress_pos;
        printf("prev: pos = %d, subj = %s, next = %d\n", prev_pos, prev.subject, prev.next_progress_pos);
        edit_progr_by_pos(prev_pos, prev);
    }

    if (info.mark == info.next_progress_pos) {
        ++info.mark;
        ++info.next_progress_pos;
    } else {
        info.next_progress_pos = get_progr_by_pos(insert_pos).next_progress_pos;
    }
    printf("insert: pos = %d, subj = %s, next = %d\n", insert_pos, progr.subject, progr.next_progress_pos);
    edit_progr_by_pos(insert_pos, progr);
    edit_progr_by_pos(-1, info);
    printf("insert progr return 1\n");
    return 1;
}

void files_init() {
    FILE *s_ind, *s_fl, *p_fl;
    s_ind = fopen("S.ind", "rb");
    if (!s_ind) {
        s_ind = fopen("S.ind", "wb");
        Index ind = {0, 0};
        fwrite(&ind, IND_SIZ, 1, s_ind);
    }
    fclose(s_ind);

    s_fl = fopen("S.fl", "rb");
    if (!s_fl) {
        s_fl = fopen("S.fl", "wb");
    }
    fclose(s_fl);

    p_fl = fopen("P.fl", "rb");
    if (!p_fl) {
        p_fl = fopen("P.fl", "wb");
        Progress info = {0, "\0", 0, 0, 0, 0,
                         "\0", 0};
        fwrite(&info, PROGR_SIZ, 1, p_fl);
    }
    fclose(p_fl);
}

void help(FILE *out) {
    fprintf(out, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    fprintf(out, "'insertm' - Insert student\n");
    fprintf(out, "'inserts' - Insert progress\n");
    fprintf(out, "'getm' - Find student\n");
    fprintf(out, "'gets' - Find progress\n");
    fprintf(out, "'updatem' - Update student\n");
    fprintf(out, "'updates' - Update progress\n");
    fprintf(out, "'delm' - Delete student\n");
    fprintf(out, "'dels' - Delete progress\n");
    fprintf(out, "'dump' - Print all students and progresses\n");
    fprintf(out, "'exit' - Close program\n");
    fprintf(out, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
}

void dump(FILE *out) {
    //printf("dump start\n");
    int siz = num_of_inds();
    fprintf(out, "Size = %d\n", siz);
    for (int i = 0; i < siz; ++i) {
        Index cur_ind = get_ind_by_pos(i);
        Student cur_stud = get_stud_by_pos(cur_ind.pos);
        fprintf(out, "%d: %-20.20s %-20.20s | %06d | %02d.%02d.%04d | %-20.20s | %-20.20s | %d | %-20.20s |\n", i + 1,
                cur_stud.last_name, cur_stud.first_name, cur_stud.gradebook_num, cur_stud.admission_date.day,
                cur_stud.admission_date.month, cur_stud.admission_date.year, cur_stud.faculty, cur_stud.specialty,
                cur_stud.course, cur_stud.group);
        if (cur_stud.first_progress_pos >= 0) {
            Progress cur_progr = get_progr_by_pos(cur_stud.first_progress_pos);
            for (int j = 0;; ++j) {
                fprintf(out, "\t%d.%d: %-20.20s | %d | %03d | %-20.20s | %02d.%02d.%04d |\n", i + 1, j + 1,
                        cur_progr.subject,
                        cur_progr.term_num, cur_progr.mark, cur_progr.teacher_last_name, cur_progr.exam_date.day,
                        cur_progr.exam_date.month, cur_progr.exam_date.year);
                //fprintf(out, "%d\n", cur_progr.next_progress_pos);
                if (cur_progr.next_progress_pos > 0) {
                    cur_progr = get_progr_by_pos(cur_progr.next_progress_pos);
                } else break;
            }
        }
    }
    //printf("dump end\n");
    fprintf(out, "\n\n");
}

void print_stud(FILE *out, Student stud) {
    fprintf(out, "%-20.20s %-20.20s | %06d | %02d.%02d.%04d | %-20.20s | %-20.20s | %d | %-20.20s |\n",
            stud.last_name, stud.first_name, stud.gradebook_num, stud.admission_date.day,
            stud.admission_date.month, stud.admission_date.year, stud.faculty, stud.specialty,
            stud.course, stud.group);
}

void print_progr(FILE *out, Progress progr) {
    fprintf(out, "\t%-20.20s | %d | %03d | %-20.20s | %02d.%02d.%04d |\n",
            progr.subject,
            progr.term_num, progr.mark, progr.teacher_last_name, progr.exam_date.day,
            progr.exam_date.month, progr.exam_date.year);
}