// ART.cpp: Лабораторная работа Толмачев 3
//

#include "stdafx.h"
#include <cstdlib> 
#include "stdio.h"
#include <conio.h> 
#include <clocale>
//Функция подсчета ненулевых элементов
double Smas(int mas []) 
{
	int one = 0;//счетчик единиц
	for (int i = 0; i < 12; i++)
	{
		if (mas[i]== 1)
			one++;
	}
	return one;

}
//Функиця подсчета ненулевых совпадений
int Coincidence(int mas1[], int mas2[])
{
	int logic=0;
	for (int i = 0; i < 12; i++)
	{
		if ((mas1[i] == mas2[i])&&( mas1[i] == 1 ))
			logic++;
	}
	return logic;

}
//Функция подсчета Bn
double Bnmas(int mas[])
{
	double L = 2;
	double B[12];
	for (int i = 0; i < 12; i++)
	{
		B[i] = (L*(double)mas[i]) / (L - 1 + Smas(mas));
	}
	for (int i = 0; i < 12; i++)
	{
		if (B[i] != 0) return B[i];
	}
	return 0;
}
//Функция сравнения
double Сomparison(int mas1[],int mas2[])
{
	int logic = 0;
	for (int i = 0; i < 12; i++)
	{
		if ((mas1[i] == mas2[i]))
			logic++;
	}
	return logic;
}
void print(int T[], double B[],int k)
{
	printf("T%i = ", k);
	for (int i = 0; i < 12; i++)
	{
		printf("%i ", T[i]);
	}
	printf("\nB%i = ", k);
	for (int i = 0; i < 12; i++)
	{
		printf("%.3lf ", B[i]);
	}
	printf("\n");
}
void B(double B[], int mas[])
{
	for (int i = 0; i<12; i++)
	{
		B[i] = ((2 * (double)mas[i]) / (1 + (double)Smas(mas)));
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	double pn = 0.9; //Пороговый уровень сходства
	int Tn[12] = { 1,1,1,1,1,1,1,1,1,1,1,1 }; // Идеальный нейрон
	int x1[12] = { 0,1,0,0,0,1,0,1,0,1,1,0 };
	int x2[12] = { 1,0,0,1,1,0,1,1,1,0,0,1 };
	int x3[12] = { 0,1,0,0,0,1,1,0,0,1,1,0 };
	int x4[12] = { 1,0,0,0,1,1,1,1,1,0,0,1 };
	int x5[12] = { 0,1,0,0,0,1,1,1,0,1,1,0 };
	double B1[12];
	double B2[12];
	double B3[12];
	double B4[12];
	double B5[12];
	int c[12], T[12];
	int kol = 0; //Количество обученных нейронов
	double Swin=0,sum=0,Sn=0;
	double S1[12];
	int L = 2;
	double B[12];
	int job = 0; //счетчик
	int k = 1; //Счетчик данных при определении победителя
	//Для идеального нейрона
	double Bn =((double)L)/(1+12);
	printf("Bn = %.3lf\n", Bn-0.01);
	Bn = Bn - 0.01;

	//Стадия 1 для х1
	printf("Стадия 1\n");
	for (int i = 0; i < 12; i++)
	{
		B[i] = (L*(double)x1[i]) / (L - 1 + Smas(x1));
		B1[i] = B[i];
	}
	for (int i = 0; i < 12; i++)
	{
		T[i] = x1[i];
	}
	print(T, B1, k);
	system("pause");

	//Стадия 2 для х2
	//На входе X2
	printf("Стадия 2\nРаспознавание\n");
	
	Sn = Coincidence(Tn,x1)* Bn;
	for (int i = 0; i < 12; i++)
	{
		sum = sum + (S1[i] * (double)x2[i]);
	}
	printf("Sn = %.3lf\n", Sn);
	k = 2;
	//Обучение нового нейрона
	for (int i = 0; i < 12; i++)
	{
		B2[i] = (L*(double)x2[i]) / (L - 1 + Smas(x2));
	}
	for (int i = 0; i < 12; i++)
	{
		T[i] = x2[i];
	}
	print(T, B2, k);
	system("pause");
	
	//Стадия 3 для х3
	//На входе Х3 
	printf("Стадия 3\n\nНа входе Х3\nВыполняется операция распознавание\n");
	//Ищем победителя
	if ((Smas(x3)*Bn) > ((double)Coincidence(x3, x1)*Bnmas(x1)))
	{
		if ((Smas(x3)*Bn) > ((double)Coincidence(x3, x2)*Bnmas(x2)))
		{
			Swin = Smas(x3)*Bn;
			k = 0;
		}
		else
		{
			Swin = ((double)Coincidence(x3, x2)*Bnmas(x2));
			k = 2;
		}
	}
	else
	{
		Swin = ((double)Coincidence(x3, x1)*Bnmas(x1));
		k = 1;
	}
	printf("SN = %lf\nS1 = %lf\nS2 = %lf\n", Smas(x3)*Bn, (double)Coincidence(x3, x1)*Bnmas(x1), (double)Coincidence(x3, x2)*Bnmas(x2));
	printf("Победитель Swin = %i) %lf\n",k,Swin);
	printf("Происходит операция сравнение\n");
	//Переобучение нейрона	
	if (pn <= (Сomparison(x1, x3))/12)
	{
		for(int i = 0; i < 12; i++)
		{
			c[i] = T[i] * x3[i];
			T[i] = c[i];
			B3[i] = (2 * x3[i]) / (2 - 1 + Smas(x3));
		}
	}
	print(T,B,k);
	

	system("pause");
	//Стадия 4 для х4
	//На входе х4
	printf("\nСтадия 4\nНа входе х4\n");
	
	if ((Smas(x4)*Bn) >((double)Coincidence(x4, x1)*Bnmas(x1)))
	{
		if ((Smas(x4)*Bn) > ((double)Coincidence(x4, x2)*Bnmas(x2)))
		{
			if ((Smas(x4)*Bn) > ((double)Coincidence(x4, x3)*Bnmas(x3)))
			{
				Swin = Smas(x4)*Bn;
				k = 0;
			}
			else
			{
				Swin = ((double)Coincidence(x4, x3)*Bnmas(x3));
				k = 3;
			}
		}
		else
		{
			Swin = ((double)Coincidence(x4, x2)*Bnmas(x2));
			k = 2;
		}
	}
	else
	{
		Swin = ((double)Coincidence(x3, x1)*Bnmas(x1));
		k = 1;
	}
	printf("SN = %lf\nS1 = %lf\nS2 = %lf\nS3 = %lf\n", Smas(x4)*Bn, (double)Coincidence(x4, x1)*Bnmas(x1), (double)Coincidence(x4, x2)*Bnmas(x2), (double)Coincidence(x4, x3)*Bnmas(x3));
	printf("Победитель Swin = %i) %lf\n", k, Swin);
	for (int i = 0; i < 12; i++)
	{
		T[i] = x2[i];
	}
	if (pn <= (Сomparison(x2, x4)) / 12)
	{
		for (int i = 0; i < 12; i++)
		{
			c[i] = T[i] * x4[i];
			T[i] = c[i];
			B[i] = (2 * x4[i]) / (2 - 1 + Smas(x4));
		}
	}
	print(T, B, k);
	
	
	system("pause");
	//Стадия 5 для х5
	//На входе х5
	printf("\nСтадия 5\nНа входе х5\n");
	if ((Smas(x5)*Bn) >((double)Coincidence(x5, x1)*Bnmas(x1)))
	{
		if ((Smas(x5)*Bn) > ((double)Coincidence(x5, x2)*Bnmas(x2)))
		{
			if ((Smas(x5)*Bn) > ((double)Coincidence(x5, x3)*Bnmas(x3)))
			{
				if ((Smas(x5)*Bn) > ((double)Coincidence(x5, x4)*Bnmas(x4)))
				{
					Swin = Smas(x5)*Bn;
					k = 0;
				}
				else
				{
					Swin = ((double)Coincidence(x5, x4)*Bnmas(x4));
					k = 4;
				}

			}
			else
			{
				Swin = ((double)Coincidence(x5, x3)*Bnmas(x3));
				k = 3;
			}
		}
		else
		{
			Swin = ((double)Coincidence(x5, x2)*Bnmas(x2));
			k = 2;
		}
	}
	else
	{
		Swin = ((double)Coincidence(x5, x1)*Bnmas(x1));
		k = 1;
	}
	printf("SN = %lf\nS1 = %lf\nS2 = %lf\nS3 = %lf\nS4 = %lf\n", Smas(x5)*Bn, (double)Coincidence(x5, x1)*Bnmas(x1), (double)Coincidence(x5, x2)*Bnmas(x2), (double)Coincidence(x5, x3)*Bnmas(x3), (double)Coincidence(x5, x4)*Bnmas(x4));
	printf("Победитель Swin = %i) %lf\n", k, Swin);
	for (int i = 0; i < 12; i++)
	{
		T[i] = x2[i];
	}
	if (pn <= (Сomparison(x1, x5)) / 12)
	{
		for (int i = 0; i < 12; i++)
		{
			c[i] = T[i] * x4[i];
			T[i] = c[i];
			B[i] = (2 * x5[i]) / (2 - 1 + Smas(x5));
		}
	}
	print(T, B, k);
	printf("\n");
	system("pause");
	system("cls");
	printf("Ответ:\nНераспределенный нейрон:\n");
	print(x1, B1, 1);
	printf("Переобученный\n");
	print(T, B, k);
	print(T, B1, 2);
	system("pause");
	return 0;
}
 
