#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LEN 10  // 姓名长度
#define MAX_STUD_LEN 30  // 学生数量
#define MAX_COUR_LEN 6   // 课程数量
typedef struct student {
  long long number;  // 用char数组也行
  char name[MAX_NAME_LEN];
  double courseGrade
      [MAX_COUR_LEN];  // 各科考试成绩，具体课程门数由键盘输入，不超过6门
  double avgGrade;
  double totalGrade;
} STUDENT;

int menu();
void ReadScore(STUDENT stu[], int *stu_sum, int *cou_sum);
void AvgScoreOfCourse(STUDENT stu[], int stu_sum, int cou_sum);
void AvgScoreOfStudent(STUDENT stu[], int stu_sum, int cou_sum);
void SortByTotalScore(STUDENT stu[], int stu_sum,
                      int (*compare)(double a, double b));
void SortByNumber(STUDENT stu[], int stu_sum);
void SortByName(STUDENT stu[], int stu_sum);
void FindByNumber(STUDENT stu[], int stu_sum, int cou_sum);
void FindByName(STUDENT stu[], int stu_sum, int cou_sum);
void StatisticAnalysis(STUDENT stu[], int stu_sum, int cou_sum);
void PrintScoreOrderly(STUDENT stu[], int stu_sum, int cou_sum);
void WriteToFile(STUDENT stu[], int stu_sum, int cou_sum, char path[]);
void ReadFromFile(STUDENT stu[], int *stu_sum, int *cou_sum, char path[]);
void AddOneRecord(STUDENT stu[], int *stu_sum, int cou_sum);
void DeleteOneRecordByNumber(STUDENT stu[], int *stu_sum, int cou_sum);
void AlterOneRecordByNumber(STUDENT stu[], int stu_sum, int cou_sum);

int Descending(double a, double b);
int Ascending(double a, double b);
int main(int argc, char const *argv[]) {
  STUDENT stu[MAX_STUD_LEN];
  int stu_sum = 0, cou_sum = 0;  // 学生数量和课程数量
  char writepath[100] = "E:/wmjcode/ExperimentWork/score_1.txt";
  char readpath[100] = "E:/wmjcode/ExperimentWork/score.txt";
  while (1) {
    int choice = menu();
    switch (choice) {
      case 0:
        printf("程序结束!");
        exit(0);
      case 1:
        ReadScore(stu, &stu_sum, &cou_sum);
        break;
      case 2:
        AvgScoreOfCourse(stu, stu_sum, cou_sum);
        break;
      case 3:
        AvgScoreOfStudent(stu, stu_sum, cou_sum);
        break;
      case 4:
        SortByTotalScore(stu, stu_sum, Descending);
        PrintScoreOrderly(stu, stu_sum, cou_sum);
        break;
      case 5:
        SortByTotalScore(stu, stu_sum, Ascending);
        PrintScoreOrderly(stu, stu_sum, cou_sum);
        break;
      case 6:
        SortByNumber(stu, stu_sum);
        PrintScoreOrderly(stu, stu_sum, cou_sum);
        break;
      case 7:
        SortByName(stu, stu_sum);
        PrintScoreOrderly(stu, stu_sum, cou_sum);
        break;
      case 8:
        FindByNumber(stu, stu_sum, cou_sum);
        break;
      case 9:
        FindByName(stu, stu_sum, cou_sum);
        break;
      case 10:
        StatisticAnalysis(stu, stu_sum, cou_sum);
        break;
      case 11:
        PrintScoreOrderly(stu, stu_sum, cou_sum);
        break;
      case 12:
        WriteToFile(stu, stu_sum, cou_sum, writepath);
        break;
      case 13:
        ReadFromFile(stu, &stu_sum, &cou_sum, readpath);
        break;
      case 14:
        AddOneRecord(stu, &stu_sum, cou_sum);
        break;
      case 15:
        DeleteOneRecordByNumber(stu, &stu_sum, cou_sum);
        break;
      case 16:
        AlterOneRecordByNumber(stu, stu_sum, cou_sum);
        break;
      default:
        printf("输入有误，请重新输入\n");
        break;
    }
  }

  return 0;
}
// 1
void ReadScore(STUDENT stu[], int *stu_sum, int *cou_sum) {
  printf("输入学生数量(n<%d):", MAX_STUD_LEN);
  scanf("%d", stu_sum);
  printf("输入课程数量(n<%d):", MAX_COUR_LEN);
  scanf("%d", cou_sum);
  printf("按行输入\nnumber\tname\t考试1成绩\t考试2成绩\t......\n");
  for (int i = 0; i < *stu_sum; i++) {
    scanf("%Id", &stu[i].number);
    scanf("%s", stu[i].name);  // 输入有空格的名字
    for (int j = 0; j < *cou_sum; j++) {
      scanf("%3.1lf", &stu[i].courseGrade[j]);
    }
  }
  printf("学生数据从键盘输入完毕！\n");
  return;
}
// 2
void AvgScoreOfCourse(STUDENT stu[], int stu_sum, int cou_sum) {
  double c[MAX_COUR_LEN];
  memset(c, 0, sizeof(c));
  for (int i = 0; i < stu_sum; i++) {
    for (int j = 0; j < cou_sum; j++) {
      c[j] += stu[i].courseGrade[j];
    }
  }
  printf("各个课程的总分和平均分如下:\n\ttotal\taverage\n");
  for (int j = 0; j < cou_sum; j++) {
    printf("课程%d:\t", j);
    printf("%3.1lf\t", c[j]);  // 总分
    printf("%3.1lf\n", stu_sum > 0 ? c[j] / stu_sum : -1);
  }
  return;
}
// 3
void AvgScoreOfStudent(STUDENT stu[], int stu_sum, int cou_sum) {
  double s[MAX_STUD_LEN];
  memset(s, 0, sizeof(s));
  for (int i = 0; i < stu_sum; i++) {
    for (int j = 0; j < cou_sum; j++) {
      s[i] += stu[i].courseGrade[j];
    }
  }
  printf("各个学生的总分和平均分如下:\n\ttotal\taverage\n");
  for (int i = 0; i < stu_sum; i++) {
    printf("学生%d:\t", i);
    printf("%3.1lf\t", s[i]);  // 总分
    stu[i].totalGrade = s[i];
    printf("%3.1lf\n", cou_sum > 0 ? s[i] / cou_sum : -1);
    stu[i].avgGrade = cou_sum > 0 ? s[i] / cou_sum : -1;
  }
  return;
}
// 4&5
void SortByTotalScore(STUDENT stu[], int stu_sum,
                      int (*compare)(double a, double b)) {
  // 简单选择排序法
  int k = 0;
  STUDENT temp;
  for (int i = 0; i < stu_sum; i++) {
    k = i;
    for (int j = i + 1; j < stu_sum; j++) {
      if ((*compare)(stu[k].totalGrade, stu[j].totalGrade) == 0) {
        k = j;  // 找到未排序数组中的最大(小)
      }
    }
    temp = stu[i];
    stu[i] = stu[k];
    stu[k] = temp;
  }
  return;
}

// 6
void SortByNumber(STUDENT stu[], int stu_sum) {
  // 简单选择排序法
  int k = 0;
  STUDENT temp;
  for (int i = 0; i < stu_sum; i++) {
    k = i;
    for (int j = i + 1; j < stu_sum; j++) {
      if (stu[k].number > stu[j].number) {
        k = j;  // 找到未排序数组中的最小
      }
    }
    temp = stu[i];
    stu[i] = stu[k];
    stu[k] = temp;
  }
  return;
}
// 7
void SortByName(STUDENT stu[], int stu_sum) {
  // 简单选择排序法
  int k = 0;
  STUDENT temp;
  for (int i = 0; i < stu_sum; i++) {
    k = i;
    for (int j = i + 1; j < stu_sum; j++) {
      if (strcmp(stu[k].name, stu[j].name) > 0) {
        k = j;  // 找到未排序数组中的最小字典序
      }
    }
    temp = stu[i];
    stu[i] = stu[k];
    stu[k] = temp;
  }
  return;
}
// 8
void FindByNumber(STUDENT stu[], int stu_sum, int cou_sum) {
  long long number;
  printf("input number:");
  scanf("%Id", &number);
  for (int i = 0; i < stu_sum; i++) {
    if (stu[i].number == number) {
      printf("%Id\t", stu[i].number);
      printf("%s\t", stu[i].name);
      for (int j = 0; j < cou_sum; j++) {
        printf("%3.1lf\t", stu[i].courseGrade[j]);
      }
      printf("%3.1lf\t", stu[i].totalGrade);
      printf("%3.1lf\t\n", stu[i].avgGrade);
    }
  }
  return;
}
// 9
void FindByName(STUDENT stu[], int stu_sum, int cou_sum) {
  char name[MAX_NAME_LEN];
  printf("intput name:");
  scanf("%s", name);
  for (int i = 0; i < stu_sum; i++) {
    if (strcmp(stu[i].name, name) == 0) {
      printf("%Id\t", stu[i].number);
      printf("%s\t", stu[i].name);
      for (int j = 0; j < cou_sum; j++) {
        printf("%3.1lf\t", stu[i].courseGrade[j]);
      }
      printf("%3.1lf\t", stu[i].totalGrade);
      printf("%3.1lf\t\n", stu[i].avgGrade);
    }
  }
  return;
}
// 10
void StatisticAnalysis(STUDENT stu[], int stu_sum, int cou_sum) {
  int t[5];
  for (int j = 0; j < cou_sum; j++) {
    memset(t, 0, sizeof(t));
    for (int i = 0; i < stu_sum; i++) {
      // 统计每个学生在course j 的表现
      if (stu[i].courseGrade[j] < 60)
        t[0] += 1;
      else if (stu[i].courseGrade[j] < 70)
        t[1] += 1;
      else if (stu[i].courseGrade[j] < 80)
        t[2] += 1;
      else if (stu[i].courseGrade[j] < 90)
        t[3] += 1;
      else
        t[4] += 1;
    }
    printf("course%d:\n", j + 1);
    printf("优秀(90~100):%d(人)", t[4]);
    printf("占比:%3.1lf%%\n",
           (stu_sum > 0 ? (double)t[4] / stu_sum : -1) * 100);
    printf("良好(80~89):%d(人)", t[3]);
    printf("占比:%3.1lf%%\n",
           (stu_sum > 0 ? (double)t[3] / stu_sum : -1) * 100);
    printf("中等(70~79):%d(人) ", t[2]);
    printf("占比:%3.1lf%%\n",
           (stu_sum > 0 ? (double)t[2] / stu_sum : -1) * 100);
    printf("及格(60~69):%d(人) ", t[1]);
    printf("占比:%3.1lf%%\n",
           (stu_sum > 0 ? (double)t[1] / stu_sum : -1) * 100);
    printf("不及格(0~59):%d(人) ", t[0]);
    printf("占比:%3.1lf%%\n",
           (stu_sum > 0 ? (double)t[0] / stu_sum : -1) * 100);
    printf("\n");
  }
  return;
}

// 11
void PrintScoreOrderly(STUDENT stu[], int stu_sum, int cou_sum) {
  for (int i = 0; i < stu_sum; i++) {
    printf("%Id\t", stu[i].number);
    printf("%s\t", stu[i].name);
    for (int j = 0; j < cou_sum; j++) {
      printf("%3.1lf\t", stu[i].courseGrade[j]);
    }
    printf("%3.1lf\t", stu[i].totalGrade);
    printf("%3.1lf\n", stu[i].avgGrade);
  }
  return;
}
// 12
void WriteToFile(STUDENT stu[], int stu_sum, int cou_sum, char path[]) {
  FILE *fp;
  if ((fp = fopen(path, "w")) == NULL) {
    printf("打开文件时出错");
    exit(0);
  }
  fprintf(fp, "%d\t", stu_sum);
  fprintf(fp, "%d\n", cou_sum);
  for (int i = 0; i < stu_sum; i++) {
    fprintf(fp, "%Id\t", stu[i].number);
    fprintf(fp, "%s\t", stu[i].name);
    for (int j = 0; j < cou_sum; j++) {
      fprintf(fp, "%3.1lf\t", stu[i].courseGrade[j]);
    }
    fprintf(fp, "%3.1lf\t", stu[i].totalGrade);
    fprintf(fp, "%3.1lf\n", stu[i].avgGrade);
  }
  fclose(fp);
  return;
}
// 13
void ReadFromFile(STUDENT stu[], int *stu_sum, int *cou_sum, char path[]) {
  FILE *fp;
  if ((fp = fopen(path, "r")) == NULL) {
    printf("打开文件时出错");
    exit(0);
  }
  fscanf(fp, "%d", stu_sum);
  fscanf(fp, "%d", cou_sum);
  for (int i = 0; i < *stu_sum; i++) {
    fscanf(fp, "%Id", &stu[i].number);
    fscanf(fp, "%s", stu[i].name);
    for (int j = 0; j < *cou_sum; j++) {
      fscanf(fp, "%lf", &stu[i].courseGrade[j]);
    }
  }
  fclose(fp);
  return;
}

// 14
void AddOneRecord(STUDENT stu[], int *stu_sum, int cou_sum) {
  if (*stu_sum >= MAX_STUD_LEN) {
    printf("超过最大学生数量\n");
    return;
  }
  printf("一次添加一条学生的记录\nnumber\tname");
  for (int i = 0; i < cou_sum; i++) {
    printf("\t考试%d成绩", i + 1);

  }
  printf("\n");
  (*stu_sum)++;
  scanf("%Id", &stu[*stu_sum - 1].number);
  scanf("%s", stu[*stu_sum - 1].name);  // 输入有空格的名字
  for (int j = 0; j < cou_sum; j++) {
    scanf("%lf", &stu[*stu_sum - 1].courseGrade[j]);
  }
  printf("添加成功!\n");
  return;
}

// 15
void DeleteOneRecordByNumber(STUDENT stu[], int *stu_sum, int cou_sum) {
  int i;
  long long number;
  printf("一次删除一条学生的记录,请输入学号:");
  scanf("%Id", &number);
  for (i = 0; i < *stu_sum; i++) {
    if (stu[i].number == number) {
      break;
    }
  }
  for (int j = i + 1; j < *stu_sum; j++) {
    stu[j - 1] = stu[j];
  }
  (*stu_sum)--;
  printf("删除成功!\n");
  return;
}

// 16
void AlterOneRecordByNumber(STUDENT stu[], int stu_sum, int cou_sum) {
  long long number;
  printf("输入想要修改的记录学号:");
  scanf("%Id", &number);
  printf("一条学生的记录\nnumber\tname");
  for (int i = 0; i < cou_sum; i++) {
    printf("\t考试%d成绩", i + 1);
  }
  printf("\n");
  for (int i = 0; i < stu_sum; i++) {
    if (stu[i].number == number) {
      scanf("%Id", &stu[i].number);
      scanf("%s", stu[i].name);  // 输入有空格的名字
      for (int j = 0; j < cou_sum; j++) {
        scanf("%lf", &stu[i].courseGrade[j]);
      }
      printf("修改完成!\n");
      return;
    }
  }
  printf("修改失败!\n");
  return;
}
int menu() {
  int ch;
  char menu_str[] =
      "1.\tInput record\n"
      "2.\tCalculate total and average score of every course\n"
      "3.\tCalculate total and average score of every student\n"
      "4.\tSort in descending order by total score of every student\n"
      "5.\tSort in ascending order by total score of every student\n"
      "6.\tSort in ascending order by number\n"
      "7.\tSort in dictionary order by name\n"
      "8.\tSearch by number\n"
      "9.\tSearch by name\n"
      "10.\tStatistic analysis for every course\n"
      "11.\tList record\n"
      "12.\tWrite to a file\n"
      "13.\tRead from a file\n"
      "0.\tExit\n";
  printf("%s", menu_str);
  scanf("%d", &ch);
  return ch;
}

int Descending(double a, double b) { return a > b ? 1 : 0; }
int Ascending(double a, double b) { return a < b ? 1 : 0; }
