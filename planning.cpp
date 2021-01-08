#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <string.h>
#define max 100

using namespace std;
typedef int typeinfo;
typedef string typefofo;
typedef struct typenode *typeptr;
struct typenode
	{
		typeinfo tgl;
		typefofo nama;
		typeinfo kat;
		typeptr next;
	};

typeptr u_dpn,u_back,awal,akhir;
typeptr NB,p_dpn,p_back,m_dpn,m_back,e_dpn,e_back,bantu;
typeinfo jq_utama=0;

struct typestack{
	typeinfo top;
	typeinfo tgl[99];
	typefofo nama[99];
	typeinfo kat[99];
};
struct typestack histori;

void input();
void main_enque(typefofo NM, typeinfo TG, typeinfo KT);
void side_enque(typefofo NM, typeinfo TG, typeinfo KT);
void side_dequeue(typeinfo KT);
void cetakqueue();
int queuekosong();
int queuepkosong(typeinfo IB);
void cetakpri(typeinfo side);
void generate();
void main_dequeue();
void push(typefofo IB,typeinfo TG,typeinfo KT);
void pop();
void cetakstack();
void buatstack();
int stackpenuh();
int stackkosong();

int main(){
	int menu;
	char balikmenu;
	
	do{
	//cout<<u_dpn<<" "<<u_back<<endl;	
	//cout<<"Histori "<<histori.top<<endl;	
		
	cout<<"--------Planning Apps---------------"<<endl;
	cout<<"1. Masukkan task"<<endl;
	cout<<"2. Cetak task"<<endl;
	cout<<"3. Rekomendasi"<<endl;
	cout<<"4. Generate Jadwal"<<endl;
	cout<<"5. Cetak Histori"<<endl;
	cout<<"6. Hapus Histori terbaru"<<endl;
	cout<<"Menu : ";cin>>menu;
	
	if(menu==1){
		input();
		jq_utama++;
		balikmenu='y';
	}
	else if(menu==2){
		cetakqueue();
		cout<<"Kembali ke menu (y/n) ? : ";cin>>balikmenu;
	}
	else if(menu==3){
		int menu3,menu31;
		system("cls");
		cout<<"Rekomendasi Tugas Anda : "<<endl;
		cout<<endl;
		cout<<"Prioritas"<<endl;
		cetakpri(1);
		cout<<endl;
		cout<<"Medium"<<endl;
		cetakpri(2);
		cout<<endl;
		cout<<"Easy"<<endl;
		cetakpri(3);
		cout<<endl;
		
		cout<<" 1. Hapus tugas"<<endl;
		cout<<" 2. Kembali ke menu"<<endl;
		cout<<"pilih : ";cin>>menu3;
		if(menu3==1){
			cout<<" Hapus Tugas : "<<endl;
			cout<<"  1. Hapus tugas dari Tugas Prioritas  "<<endl;
			cout<<"  2. Hapus tugas dari Tugas Medium  "<<endl;
			cout<<"  3. Hapus tugas dari Tugas Easy  "<<endl;
			cout<<"  pilih :";cin>>menu31;
				if(menu31==1){
					side_dequeue(1);}
				else if(menu31==2){
					side_dequeue(2);}
				else{
					side_dequeue(3);}
					
				balikmenu='y';
		}
		else{
			balikmenu='y';
		}
		
		//cout<<"Kembali ke menu (y/n) ? : ";cin>>balikmenu;
	}
	else if(menu==4){
		generate();
		balikmenu='y';
	}
	
	else if(menu==5){
		cetakstack();
		cout<<"Kembali ke menu (y/n) ? : ";cin>>balikmenu;
	}
	else if(menu==6){
		pop();
		balikmenu='y';
	}
	
	
		system("cls");
	}while(balikmenu=='y'||balikmenu=='Y');
}

void input(){
	typefofo nama;
	typeinfo tgl,kat;
	
	cin.ignore();
	cout<<"Masukkan Judul : ";getline(cin,nama);
	cout<<"Masukkan Tanggal : ";cin>>tgl;
	cout<<"Kategori Tugas : "<<endl;
	cout<<"  1. Prioritas  "<<endl;
	cout<<"  2. Standart  "<<endl;
	cout<<"  3. Easy  "<<endl;
	cout<<"Masukkan Kategori : ";cin>>kat;
	main_enque(nama,tgl,kat);
}

void main_enque(typefofo NM, typeinfo TG, typeinfo KT){
	 typeptr NB, bantu;
	 NB= new typenode;
	 NB->nama=NM;
	 NB->tgl=TG;
	 NB->kat=KT;
	 NB->next=NULL;
		 if (queuekosong()){ 
			 u_dpn=NB;
			 u_back=NB; 
		}
		else if(TG<=u_dpn->tgl){
			NB->next=u_dpn;
			  u_dpn=NB;
		}
		else{
			bantu=u_dpn;
			while(bantu->next!=NULL && TG>bantu->next->tgl){
				bantu=bantu->next;
			}
				NB->next=bantu->next;
				bantu->next=NB;
				if(TG>u_back->tgl)
					u_back=NB;
		}
		
}

void generate(){
	while(u_dpn!=u_back){
		typefofo nama;
		typeinfo tgl,kat;
			nama=u_dpn->nama;
			tgl=u_dpn->tgl;
			kat=u_dpn->kat;
		side_enque(nama,tgl,kat);
		main_dequeue();
	}	
}

void main_dequeue(){
 typeptr hapus;
	 if (queuekosong()){
	 cout << "Queue masih kosong !";
	 }
	 else{ 
		hapus=u_dpn;
		u_dpn=hapus->next;
	 }
}

void cetakqueue(){	
	typeptr bantu;
	bantu=u_dpn;
	 while (bantu!=NULL){
		cout << " " << bantu->nama<<endl;
		cout << " " << bantu->tgl<<endl;
		cout<<endl;
		bantu=bantu->next;
	 }
}

void cetakpri(typeinfo side){	
	typeptr bantu;
	if(side==1){
		bantu=p_dpn;}
	else if(side==2){
		bantu=m_dpn;}
	else{ 
		bantu=e_dpn;}
	 while (bantu!=NULL){
		cout << "-- | " << bantu->nama<<" ,tgl:"<<bantu->tgl<<" |";
		bantu=bantu->next;
	 }
	 cout<<endl;
}

int queuekosong(){ 
	if(u_dpn==NULL)
		return(true);
	else
		return(false);
}

int queuepkosong(typeinfo IB){ 
	typeptr bantu;
	if(IB==1)
		bantu=p_dpn;
		else if(IB==2)
			bantu=m_dpn;
			else
				bantu=e_dpn;
				
	if(bantu==NULL)
		return(true);
	else
		return(false);
}
	
void side_dequeue(typeinfo KT){
 typeptr hapus;
		 if(KT==1){
			  hapus=p_dpn;
			  p_dpn=hapus->next;
		   }else if(KT==2){
			    hapus=m_dpn;
				m_dpn=hapus->next;
			}else{
				 hapus=e_dpn;
				 e_dpn=hapus->next;
			  }
		push(hapus->nama,hapus->tgl,hapus->kat);
		free(hapus);
}

void side_enque(typefofo NM, typeinfo TG, typeinfo KT){	
	NB= new typenode;
	 NB->nama=NM;
	 NB->tgl=TG;
	 NB->kat=KT;
	 NB->next=NULL;
	 
	  if (queuepkosong(KT)){
		  if(KT==1){
			  p_dpn=NB;
			  p_back=NB; 
		   }else if(KT==2){
			   m_dpn=NB;
			   m_back=NB;
			}else{
				e_dpn=NB;
			    e_back=NB;
			  }
		}
		 else{ 
			  if(KT==1){
				bantu=p_back;
				bantu->next=NB;
				NB->next=NULL; 
				p_back=NB;
			  }else if(KT==2){
				  bantu=m_back;
				  bantu->next=NB;
				  NB->next=NULL; 
				  m_back=NB;
			  }else{
				  bantu=e_back;
				  bantu->next=NB;
				  NB->next=NULL; 
				  e_back=NB;
			  }  
		 }
}

//-----------------Satck--------------------------------

int stackkosong(){ 
	if (histori.top==-1)
		return(true);
	else
		return(false); 
}

int stackpenuh(){ 
	if (histori.top==max)
		return(true);
	else
		return(false); 
}

void buatstack(){ 
	histori.top=0; 
}

void cetakstack(){
 int i=0;
 while (i<histori.top){ 
	 cout << " | " << histori.nama[i]<<" ,tgl:"<<histori.tgl[i]<<" ,kat:"<<histori.kat[i]<<" |"<<endl;
	 i++;
 }
}

void pop(){ 
	string IP;
	int htgl,hkat;
	if(stackkosong())
		cout << "stack underflow\n";
	else{
		IP=histori.nama[histori.top];
		htgl=histori.tgl[histori.top];
		hkat=histori.kat[histori.top];
		histori.top--;
	}; 
}

void push(typefofo IB,typeinfo TG,typeinfo KT){ 
	if(stackpenuh())
		cout << "stack overflow\n";
	else{
		
		histori.nama[histori.top]=IB;
		histori.tgl[histori.top]=TG;
		histori.kat[histori.top]=KT;
		histori.top++;
		}
}

