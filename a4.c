/*****************************************
* @Instructor: Prof. Alaa Mohammed Salih *
* @Autor: Alqassam Firwana		 *
* @id: 00000000 0			 *
* @course: PROG20799			 *
* @Assignment: 4			 *
* @Date: July 2021			 *
*****************************************/
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*********************************************************************************
 * MY COLORS <-- this time will make it more  					 *
 * readable without cluttering my code						 *
 * @source https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a *
 *********************************************************************************/
//Regular text
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

//Regular bold text
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"
//reset
#define reset "\e[0m"
#define STR_LEN 20
#define ARR_LEN 20

/**********************************************
 *               My Structures                *
 **********************************************/
struct student
{
	int studId;
	char fname[STR_LEN];
	char lname[STR_LEN];
	int age;
	char course_code[40];
	int grade[4];
	int total_grades;
	float per;
	struct student *next;
};

struct student stu[ARR_LEN];
struct student sortedStudent[ARR_LEN];
int counter = 0;
int validCheck;
int vr;
bool calculated = false;
/****************************************************
 *               Functions Prototypes               *
 ****************************************************/
int locate_student(int id);
void createStudent();
void markfunc();
void stuFunc();
void calculateTotal();
void InsertSort();
void swap(float *num1, float *num2);
int partition(float myArr[], int low, int high);
void quickSort(float array[], int low, int high);
void quickSortPercentage();
int binarySearch(struct student arr[], int l, int r, int id);
void printStu(int in);
int validate(int valid);
void isEmpty();
void isCalculated();
int validateMark(int m);
void empty_stdin();
/****************************************************
 *               Locate Student                     *
 ****************************************************/
int locate_student(int id)
{

	for (int i = 0; i < counter; i++)
	{
		;
		if (id == stu[i].studId)
		{
			//return index of student
			return i;
		}
	}
	//not found
	return -1;
}

/****************************************************
 *               Create Student                     *
 ****************************************************/
void createStudent()
{
	printf(BLU "\n-------------------------------\n");
	printf(BLU "|" BYEL "  Create New Student Record  " BLU "|\n");
	printf("-------------------------------\n");
id:
	printf(BLU "Student Id: " reset);
	int tempId;
	validCheck = scanf("%d", &tempId);
	vr = validate(validCheck);
	if (vr == -1)
		goto id;
	if (locate_student(tempId) != -1)
	{
		char x;
		printf(BRED "\nStudent number already exists, try new one!, Press Enter to continue...\n" reset);
		while ((x = getchar()) != '\n' && x != EOF)
			;
		scanf("%c", &x);
		goto id;
	}
	else
		stu[counter].studId = tempId;

	printf(BLU "First Name: " reset);
	scanf("%s", stu[counter].fname);
	printf(BLU "Last Name: " reset);
	scanf("%s", stu[counter].lname);
age:
	printf(BLU "Age: " reset);
	validCheck = scanf("%d", &stu[counter].age);
	vr = validate(validCheck);
	if (vr == -1)
		goto age;
	printf(BLU "Course Code: " reset);
	scanf("%s", stu[counter].course_code);
	printf(BGRN "\n\nNew Student Record Entered Successfully !\n\n" reset);
	counter++;
}

/****************************************************
 *               Marks Entery                       *
 ****************************************************/
void markfunc()
{
	if (counter == 0)
	{
		isEmpty();
		return;
	}
	printf(BLU "\n-------------------------\n");
	printf(BLU "|" BYEL "Student Marks Registery" BLU "| \n");
	printf("-------------------------\n");
	for (int i = 0; i < counter; i++)
	{
		printf(BLU "Marks For Student id " MAG " %d\n" reset, stu[i].studId);
		for (int a = 0; a < 4; a++)
		{
			int temp;
		grade:
			printf(CYN "Grade for Course %d: " reset, (a + 1));
			validCheck = scanf("%d", &temp);
			vr = validate(validCheck);
			if (vr == -1)
				goto grade;
			int mrkCeck = validateMark(temp);
			if (mrkCeck == -1)
				goto grade;
			stu[i].grade[a] = temp;
		}
	}
}

/****************************************************
 *               Update Student                     *
 ****************************************************/
void stuFunc()
{
sid:
	printf(BLU "Enter Student Id To Modify: " reset);
	char tempStr[20];
	tempStr[0] = '\0';
	int id;
	validCheck = scanf("%d", &id);
	vr = validate(validCheck);
	if (vr == -1)
		goto sid;
	int stloc = 1;
	stloc = locate_student(id);
	if (stloc == -1)
	{
		printf(BRED "\nStudent Not Found !\n");
	}
	else
	{
		printf(BLU "Enter field no to modify\n"
			   "1. First Name\n"
			   "2. Last Name\n"
			   "3. Student Id\n"
			   "4. Age\n"
			   "5. Courses name\n"
			   "6. All Grades\n"
			   "7. One Course Grade\n");
		int opt;
		scanf("%d", &opt);
		switch (opt)
		{
		case 1:
			printf(BYEL "Current First Name: %s\n" BLU, stu[stloc].fname);
			printf("New First Name: ");
			printf(reset);
			scanf("%s", tempStr);
			strcpy(stu[stloc].fname, tempStr);
			break;
		case 2:
			printf(BYEL "Current Last Name: %s\n" BLU, stu[stloc].lname);
			printf("\nNew Last Name: ");
			printf(reset);
			scanf("%s", tempStr);
			strcpy(stu[stloc].lname, tempStr);
			break;
		case 3:
			printf(BYEL "Current Id: %d\n" BLU, stu[stloc].studId);
			printf("\nNew Student Id: ");
			printf(reset);
			scanf("%d", &stu[stloc].studId);
			break;
		case 4:
			printf(BYEL "Current Age: %d\n" BLU, stu[stloc].age);
			printf("\nNew Age: ");
			printf(reset);
			scanf("%d", &stu[stloc].age);
			break;
		case 5:
			printf(BYEL "Current Course: %s\n" BLU, stu[stloc].course_code);
			printf("\nNew Course name: ");
			printf(reset);
			scanf("%s", tempStr);
			strcpy(stu[stloc].course_code, tempStr);
			break;
		case 6:
			printf("All Grades \n");
			int t;
			for (int a = 0; a < 4; a++)
			{
			case6:
				printf(BYEL "Current course %d grade: %d\n", a + 1, stu[stloc].grade[a]);
				printf(BLU "New Grade %d: ", (a + 1));
				printf(reset);
				validCheck = scanf("%d", &t);
				vr = validate(validCheck);
				if (vr == -1)
					goto case6;
				int mrkCeck = validateMark(t);
				if (mrkCeck == -1)
					goto case6;
				stu[stloc].grade[a] = t;
			}
			break;
		case 7:
		case7:
			printf(BLU "One Grade \n");
			printf("Enter Course No. 1~4: \n");
			int new;
			printf(reset);
			validCheck = scanf("%d", &new);

			vr = validate(validCheck);
			if (vr == -1)
				goto case7;
			int newNum = new - 1;
			if (newNum < 0 || newNum > 3)
			{
				char x;
				printf(BRED "\nPlease Enter value 1 ~ 4!, Press Enter to continue...\n" reset);
				while ((x = getchar()) != '\n' && x != EOF)
					;
				scanf("%c", &x);
				goto case7;
			}
		case72:
			printf(BYEL "Current course %d grade: %d\n", new, stu[stloc].grade[newNum]);
			printf(BLU "New Grade for Course %d: ", new);
			printf(reset);
			int newMark;
			validCheck = scanf("%d", &newMark);
			vr = validate(validCheck);
			if (vr == -1)
				goto case72;
			int mrkCeck = validateMark(newMark);
			if (mrkCeck == -1)
				goto case72;
			stu[stloc].grade[newNum] = newMark;
			break;
		default:
			printf(BRED "Invalid option\n");
			break;
		}
		printf(BGRN "\nStudent %d Record Updated.\n" reset, stu[stloc].studId);
	}
}

/****************************************************
 *               Calcualte Total & Percentage       *
 ****************************************************/
void calculateTotal()
{
	if (counter == 0)
	{
		isEmpty();
		return;
	}
	else
	{
		printf(CYN "\n------------------------------------------------------------------------------------------\n");
		printf(BYEL "St_ID\tCourse_01\tCourse_02\tCourse_03\tCourse_04\tTotal\tPercentage\n" CYN);
		printf("------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < counter; i++)
		{
			stu[i].total_grades = stu[i].grade[0] + stu[i].grade[1] + stu[i].grade[2] + stu[i].grade[3];

			stu[i].per = (float)stu[i].total_grades / 4;

			//printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%f", stu[i].studId, stu[i].grade[0], stu[i].grade[1], stu[i].grade[2], stu[i].grade[3], stu[i].total_grades, stu[i].per);
			printf(CYN "%-5d\t%-9d\t%-9d\t%-9d\t%-9d\t%-5d\t%-6.2f%%\n", stu[i].studId, stu[i].grade[0], stu[i].grade[1], stu[i].grade[2], stu[i].grade[3], stu[i].total_grades, stu[i].per);
		}
		printf("------------------------------------------------------------------------------------------\n" reset);

		calculated = true;
	}
}

/****************************************************
 *               Insertion Sort                     *
 ****************************************************/
void InsertSort()
{
	if (counter == 0)
	{
		isEmpty();
		return;
	}
	int sortedArr[counter];
	for (int i = 0; i < counter; i++)
	{
		sortedArr[i] = stu[i].studId;
	}
	int i, k, j;
	for (i = 1; i < counter; i++)
	{
		k = sortedArr[i];
		j = i - 1;

		while (j >= 0 && sortedArr[j] > k)
		{
			sortedArr[j + 1] = sortedArr[j];
			j = j - 1;
		}
		sortedArr[j + 1] = k;
	}
	printf(CYN "\n-----------------------------------------------------------\n");
	printf(BYEL "St_ID\tLast Name\tFirst Name\tAge\tCourse Code\n" CYN);
	printf("-----------------------------------------------------------\n");
	for (int k = 0; k < counter; k++)
	{
		for (int j = 0; j < counter; j++)
		{
			if (sortedArr[k] == stu[j].studId)
			{
				//Save sorted, to pass it to Binary
				sortedStudent[k] = stu[j];
				printf("%-5d\t%-9s\t%-9s\t%-3d\t%-11s\n", stu[j].studId, stu[j].lname, stu[j].fname, stu[j].age, stu[j].course_code);
			}
		}
	}
	printf("-----------------------------------------------------------\n");
	printf(reset);
}

/****************************************************
 *               Quick Sort - Recurseive            *
 ****************************************************/
void swap(float *num1, float *num2)
{
	float temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

int partition(float myArr[], int low, int high)
{
	int pivot = myArr[high];
	int i = (low - 1);
	for (int j = low; j <= high - 1; j++)
	{

		if (myArr[j] < pivot)
		{
			i++;
			swap(&myArr[i], &myArr[j]);
		}
	}
	swap(&myArr[i + 1], &myArr[high]);
	return (i + 1);
}

void quickSort(float array[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(array, low, high);
		quickSort(array, low, pi - 1);
		quickSort(array, pi + 1, high);
	}
}

void quickSortPercentage()
{
	if (counter == 0)
	{
		isEmpty();
		return;
	}
	if (calculated == false)
	{
		isCalculated();
		return;
	}
	float new_arr[counter];
	//struct student newStuArr[counter];
	for (int i = 0; i < counter; i++)
	{
		new_arr[i] = stu[i].per;
	}
	quickSort(new_arr, 0, counter - 1);
	printf(CYN "\n------------------------------------------------------------------------------------------\n");
	printf(BYEL "St_ID\tCourse_01\tCourse_02\tCourse_03\tCourse_04\tTotal\tPercentage\n" CYN);
	printf("------------------------------------------------------------------------------------------\n");
	for (int c = counter - 1; c >= 0; c--)
	{
		for (int i = 0; i < counter; i++)
		{
			if (new_arr[c] == stu[i].per)
			{
				printf("%-5d\t%-9d\t%-9d\t%-9d\t%-9d\t%-5d\t%-6.2f%%\n", stu[i].studId, stu[i].grade[0], stu[i].grade[1], stu[i].grade[2], stu[i].grade[3], stu[i].total_grades, stu[i].per);
			}
		}
	}
	printf(CYN "------------------------------------------------------------------------------------------\n");
	printf(reset);
}

/****************************************************
 *               Binary Search - Iterative          *
 ****************************************************/
int binarySearch(struct student arr[], int l, int r, int id)
{

	if (counter == 0)
	{
		isEmpty();
		return -1;
	}
	while (l <= r)
	{
		int m = l + (r - l) / 2;
		// Check mid
		if (arr[m].studId == id)
			return m;
		// If id more, ignore left part
		if (arr[m].studId < id)
			l = m + 1;
		// If id is lower, ignore right part
		else
			r = m - 1;
	}
	// not fount
	return -1;
}

void printStu(int in)
{
	if (in == -1)
	{
		printf(BRED "\nStudent Record Not Found !, Or List Not Sorted, Try Option 5 First! \n" reset);
		return;
	}
	printf(CYN "\n------------------------------------------------------------------------------------------\n");
	printf(BYEL "St_ID\tCourse_01\tCourse_02\tCourse_03\tCourse_04\tTotal\tPercentage\n" CYN);
	printf("------------------------------------------------------------------------------------------\n");

	printf("%-5d\t%-9d\t%-9d\t%-9d\t%-9d\t%-5d\t%-6.2f%%\n", sortedStudent[in].studId, sortedStudent[in].grade[0], sortedStudent[in].grade[1], sortedStudent[in].grade[2], sortedStudent[in].grade[3], sortedStudent[in].total_grades, sortedStudent[in].per);
	printf(CYN "------------------------------------------------------------------------------------------\n");

	return;
}

/****************************************************
 *               Validations                        *
 ****************************************************/
int validate(int valid)
{
	char x;
	if (valid != 1)
	{

		printf(BRED "\nPlease Enter numeric value only!, Press Enter to continue...\n" reset);
		while ((x = getchar()) != '\n' && x != EOF)
			;
		scanf("%c", &x);
		return -1;
	}
	return 0;
}

int validateMark(int mark)
{
	char x;
	if (mark < 0 || mark > 100)
	{

		printf(BRED "\nGrade Shoud Be Between 0 - 100 !, Press Enter to continue...\n" reset);
		while ((x = getchar()) != '\n' && x != EOF)
			;
		scanf("%c", &x);
		return -1;
	}
	return 0;
}

void isEmpty()
{

	char x;

	printf(BRED "\nStudents Record is Empty!, Press Enter to continue...\n" reset);
	while ((x = getchar()) != '\n' && x != EOF)
		;
	//scanf("%c", &x);
	return;
}
void isCalculated()
{
	char x;
	printf(BRED "\nCalculate Students Grades First - option 4!, Press Enter to continue...\n" reset);
	while ((x = getchar()) != '\n' && x != EOF)
		;
	return;
}

void empty_stdin(void)
{
	int c = getchar();

	while (c != '\n' && c != EOF)
		c = getchar();
}

void printFront()
{
	printf(BMAG "\t\t\t\t+==================================================+\n");
	printf("\t\t\t\t+                                                  +\n");
	printf("\t\t\t\t+" BGRN "          Student Record Managment System         " BMAG "+\n");
	printf("\t\t\t\t+                                                  +\n");
	printf("\t\t\t\t +" GRN "             PROG20799 - Assignment 4           " BMAG "+\n");
	printf("\t\t\t\t  +" GRN "               Sheridan College \u00A9           " BMAG "  +\n");
	printf("\t\t\t\t   +===========================================+\n" CYN);
	printf("\n\n");
}

int main()
{ //main start
	printFront();
	int option;
	int validNum;
	int checker;
	int id;
	clock_t begin, end;
	double time_spent;
	do
	{

	list: //list label
		printf(BCYN "\n+===================================+\n");
		printf("+                                   +\n");
		printf("+" BRED "     Please enter your option      " BCYN "+\n");
		printf("+                                   +\n");
		printf("+===================================+\n" CYN);
		printf("1. Create New Student Information.\n");
		printf("2. Update student information and marks By Id. \n");
		printf("3. Marks Entry Of Each student (courses 01-04). \n");
		printf("4. Calculate Total and Percentage. \n");
		printf("5. Insertion Sort-Display Students information in Sorted order by ID. \n");
		printf("6. Quick Sort-Display Students Percentage in Descending Order. \n");
		printf("7. Binary Search Student Record.\n");
		printf("8. Quit \n");
		printf(BGRN "Enter option: " reset);
		int ch;
		printf(BMAG);
		fflush(stdin);
		validNum = scanf("%d", &option);
		checker = validate(validNum);
		if (checker == -1)
			goto list;
		while ((ch = getchar()) != '\n')
			;
		printf(reset);
		switch (option)
		{
		case 1:
			//int id, char *fname, char *lname, int age, char *course_code, struct student *head
			createStudent();
			break;
		case 2:
			stuFunc();
			break;
		case 3:
			markfunc();
			break;
		case 4:
			calculateTotal();
			break;
		case 5:
			begin = clock();
			InsertSort();
			end = clock();
			time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			printf(MAG "\n\nInsersion Sort took %f seconds to execute\n\n" reset, time_spent);
			break;
		case 6:
			begin = clock();
			quickSortPercentage();
			end = clock();
			time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			printf(MAG "\n\nQuick Sort took %f seconds to execute\n\n" reset, time_spent);
			break;
		case 7:
		case7:
			printf("Enter Student id: \n");
			validNum = scanf("%d", &id);
			checker = validate(validNum);
			if (checker == -1)
				goto case7;
			begin = clock();
			int s = binarySearch(sortedStudent, 0, counter - 1, id);
			printf("Num: %d\n", s);
			end = clock();
			time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			printStu(s);
			printf(MAG "\n\nBinary Search took %f seconds to execute\n\n" reset, time_spent);

			break;
		case 8:
			exit(0);
			break;
		default:
			printf(BRED "\nInvalid Option !\n" reset);
			break;
		}

	} while (option != 8);

	return 0;
} //main  end
