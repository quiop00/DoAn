#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cstring>
#include <fstream>
#define INP "input.INP"
#define OUT "output.OUT"
using namespace std;

int **G;	// ma tran trong so
int n;		// so phan tu cua do thi
void input_file()
{
	ifstream inp(INP);
	if (inp == NULL)
	{
		cout<<"No found file input";
		return;
	}
	inp >> n ;
	G = new int *[n];
 
	for (int i=0; i<n; i++)
	{
		G[i] = new int [n];
		for (int j=0; j<n; j++)
			inp >> G[i][j];
	}
	inp.close();
}
 
void input_B_E(int &a)
{
	a =  0;
	cout<<endl<<"Cac dinh danh so tu 1 den "<<n<<endl;
	cout<<"Nhap dinh bat dau : ";
    while (a<1 || a> n)
    {
    	cin>>a;
    	if (a<1 || a> n)
    		cout<<"Khong hop le ! \nNhap lai dinh bat dau : ";
    }
    a -- ;

}
 
void output_file()
{
	//ofstream out(OUT);
	ofstream out;
	out.open(OUT);
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			cout<<setw(2)<<G[i][j];
			out<<setw(2)<<G[i][j];
		}
		cout<<endl;
		out<<endl;
	}
	out.close();
}
 
void Menu(int &select)
{
	cout<<endl<<"Moi ban chon thuat toan :"<<endl;
	cout<<"1: Thuat toan Dijkstra"<<endl;
	cout<<"2: Thoat !"<<endl;
	cin >> select;
}
 
void Dijkstra(int a)
{
	ofstream out;
	out.open(OUT);
	// Len[i] - Gia tri nho nhat tu a -> i. Len1 danh dau do dai.
	int Len[n];
	int S[n];                             //Danh dau dinh thuoc danh sach dac biet
	int P[n];                             //truy vet
	int infinity = 0;
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			infinity += G[i][j];
			
	for (int i = 0; i < n; i++) {
        Len[i] = infinity;                   // khoi tao do dai tu a toi moi dinh la vo cung
        S[i] = 0;                            // danh sach cac diem da xet
        P[i] = a;                            // dat diem bat dau cua moi diem la a
    }
	Len[a] = 0;	                           	 // khoi tao do dai tu a->a = 0
	int i = a, dem = 0, space = 10;
	//in ra hang tieu de
	char Vi[10];
	strcpy(Vi,"-");
	out<<setw(space+2)<<"T |";
	out<<setw(6)<<"Vi |";
	for (int i=0; i<n; i++)
	{ 
		out<<setw(space)<<i+1;
	}
	out <<endl;
	for (int i=0; i< (space) + n*11; i++)
		out<<"-";
	out<<endl;
	//ket thuc in ra hang tieu de
	string v="{";
	char temp[100];
	for(int i=1;i<=8;i++){
		sprintf(temp,"%d",i);
		v+=temp;
	}
	v+="}";
	for (int k=0; k<n; k++)
	{
	
		//tim do dai ngan nhat trong cac dinh		
		for (i=0; i<n; i++) // tim v thuoc (V-S) va Len[v] < vo cung
			if (!S[i] && Len[i] <infinity )
				break;
		for (int j = i+1 ; j<n; j++)	// tim dinh co Len min
			if (!S[j] && Len[j] < Len[i])
				i = j;
		S[i] = 1;	
 		//--------Tinh do dai tu dinh dang xet toi cac dinh tiep
 
		for (int j = 0; j<n; j++) //thay doi do dai neu co
		{
			if (!S[j] && G[i][j])
				if (Len[i] + G[i][j] < Len[j])
				{
					Len[j] = Len[i] + G[i][j];
					P[j] = i; //truy vet
				}
		}	
		dem ++;
		char *s = new char [100];
		
		out<<setw(space/2-2)<<v<<" |";
		out<<setw(4)<<Vi<<" |";
		//----------In ra gia tri moi lan lap------------
		if (dem > 0) 
		
			for (int j=0; j<n; j++)
			{	
				char temp[100];
				strcpy(s," ");
				if (dem >1 && j != i && S[j])
					sprintf(s,"%c",'-');
				else
				{
					if (j == i || (dem == 1 && j == a)){
							strcat(s,"*");
							//if(j==l){
							sprintf(temp,"%d",j+1);
							int found=v.find(temp);
							v.erase(v.begin() + found);
							v+=" ";
							strcpy(Vi,temp);
						//	}
						}	
						
					strcat(s,"[");
					if ( j != i && !S[j] && Len[j] == infinity)
						sprintf(temp,"%c,",'~');
		
					else
						sprintf(temp,"%d,",Len[j]);
					strcat(s,temp);
					if (j!=a && k==0)
						sprintf(temp, "%c", '~');
					else sprintf(temp, "%d", P[j]+1);	
					strcat(s,temp);
					strcat(s,"]");
 
				}
				out<<setw(space)<<s;
			}
 
		//----------Ket thuc In ra gia tri moi lan lap------------
		out<<endl;			
	}
	//Ket luan duong di
	for(int j=0;j<n;j++){
		if(a!=j){
			out<<endl;
			out<<"Do dai ngan nhat cua duong di tu "<<a+1	<<" den "<<j+1<<" la "<<Len[j]<<endl;
			i = j;
			char *s, *temp;
			s = new char [100];
			temp = new char [100];
			sprintf(s,"%d",i+1);
			while (i!=a)
			{
				sprintf(temp,"%s"," --> ");
				strcpy(s,strcat(temp,s));
				sprintf(temp,"%d",P[i] +1);
				strcpy(s,strcat(temp,s));
				i = P[i];
			}	
			out<<s<<endl;
			}
   }
	cout<<"Hoan thanh ! Mo file output.out de xem ket qua !";
	out.close();
	//return Len[b];
}
int main()
{
	input_file();
	int a, b, i, select = 1;
	output_file();
	while (select)
	{
		Menu(select);
		switch (select)
		{
			case 1:
			{
				cout<<endl<<"-----Thuat toan Dijkstra-----"<<endl;
				input_B_E(a);
				Dijkstra( a);
				system("pause");
				break;
			} 
			
		}
		if (select == 2) break;
	}
	system("pause");
	return 0;
}
 
 
