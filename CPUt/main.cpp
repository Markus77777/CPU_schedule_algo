/*�Ѯv����
p1 10 0 4
p2 2 1 1
p3 4 3 3
p4 1 4 2
p5 5 2 5
*/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void FCFS(string[],int[],int[],int);   //Declare function prototype.
void SJF(string[],int[],int[],int);
void priority(string[],int[],int[],int[],int);
void RR(string[],int[],int[],int);
void gantt(vector<string>,int[],int);
int main()
{
    string  nam[5]={};
    int cpuT[5]={};
    int arv[5]={};
    int pri[5]={};
    for(int i=0;i<5;++i){
        cout<<"�Ф��O��J��"<<i+1<<"��CPU�W�١BCPU�ɶ��B��F�ɶ��B�u���v:  ";
        cin>>nam[i]>>cpuT[i]>>arv[i]>>pri[i];
    }
    int ttime=0;
    for(int i=0;i<5;++i){
        ttime+=cpuT[i];
    }
   FCFS(nam,cpuT,arv,ttime); //�I�sFCFS
   SJF (nam,cpuT,arv,ttime);
   priority(nam,cpuT,arv,pri,ttime);
   RR(nam,cpuT,arv,ttime);
    return 0;
}

void gantt(vector<string> gant,string nam[5],int arv[5],int ttime){
    cout<<"gantt��"<<endl;
    cout<<"|"<<gant[0];
    for(int i=0;i<ttime-1;++i){
        if(gant[i]==gant[i+1]){
            cout<<"  ";
        }else{
            cout<<"|"<<gant[i+1];
        }
    }
    cout<<"|"<<endl;

    cout<<"0"<<"  ";
    for(int i=0;i<ttime-1;++i){
        if(gant[i]==gant[i+1]){
            cout<<"  ";
        }else{
            if(i+1<10)
            cout<<i+1<<"  ";
            else
             cout<<i+1<<" ";
        }
    }
    cout<<""<<ttime<<endl<<"----------------------------------------------------------------"<<endl;

    int rtime[5]={0}; //�����ɶ��}�C
    cout<<"�^�_�ɶ�"<<endl;
    for(int i=ttime-1;i>=0;--i){
        for(int j=0;j<5;++j){
            if(nam[j]==gant[i]&&rtime[j]<i){
                rtime[j]=i+1;
            }
        }
    }
    for(int j=0;j<5;++j){
        cout<<nam[j]<<"="<<rtime[j]-arv[j]<<"  "; //�����ɶ����F�ɶ�
        }
    cout<<endl;

    int wtime[5]={ttime,ttime,ttime,ttime,ttime}; //�s���`���ݮɶ�(���p��F�ɶ��M�����ɶ�)
    cout<<"���ݮɶ�"<<endl;
    for(int i=0;i<ttime;++i){
        for(int j=0;j<5;++j){
            if(nam[j]==gant[i]){
                wtime[j]-=1;
            }
        }
    }
    for(int j=0;j<5;++j){
        cout<<nam[j]<<"="<<wtime[j]-(ttime-rtime[j])-arv[j]<<"  "; //�����ɶ����F�ɶ�
        }
    cout<<endl<<"-----------------------------------------------------------------------------------------------------"<<endl;
     gant.clear();

}

void  FCFS(string nam[5],int cpuT[5],int arv[5],int ttime){

    vector<string> gant; //�s��̯S��
    vector<string> v;
    for(int i=0;i<ttime;++i){
        for(int j=0;j<5;++j){      //�����F�ɶ��A���쪺��i�hv�}�C
            if(arv[j]==i){
                v.push_back(nam[j]);
            }
        }

    }
    for(int i=0;i<5;++i){
        for(int j=0;j<5;++j){       //�̷�v�}�C���ƯZ���ǡA�C���ɶ���igant�}�C
            if(v[i]==nam[j]){
                for(int k=0;k<cpuT[j];k++){
                    gant.push_back(nam[j]);
                }
            }

        }
    }
    cout<<"-----------------------------------------------------------------------------------------------------";
    cout<<endl<<"FCFS"<<endl;
    gantt(gant,nam,arv,ttime);
}

void SJF(string nam[5],int cpuT1[5],int arv[5],int ttime){
    vector<string> gant; //�s��̯S��
    string arrive[5]={};
    string minT;
    int cpuT[5];
    for(int i=0;i<5;++i)
        cpuT[i]=cpuT1[i];
    for(int i=0;i<ttime;++i){
        for(int j=0;j<5;++j){
            if(arv[j]==i)
                arrive[j]=nam[j];
        }
        int min=9999;
        for(int k=0;k<5;++k){
            if(!arrive[k].empty() && cpuT[k]>0 && cpuT[k]<min){
                min=cpuT[k];
                minT=nam[k];
            }
        }
        gant.push_back(minT);
        for(int m=0;m<5;++m){
            if(minT==nam[m])
               cpuT[m]-=1;
        }
    }
    cout<<"-----------------------------------------------------------------------------------------------------";
    cout<<endl<<"SJF"<<endl;
    gantt(gant,nam,arv,ttime);

}

void priority (string nam[5],int cpuT1[5],int arv[5],int pri[5],int ttime){
    vector<string> gant; //�s��̯S��
    string arrive[5]={};
    string priT;
    int cpuT[5];
    for(int i=0;i<5;++i)
        cpuT[i]=cpuT1[i];
    for(int i=0;i<ttime;++i){
        for(int j=0;j<5;++j){
            if(arv[j]==i)
                arrive[j]=nam[j];
        }
        int minpri=9999;
        for(int k=0;k<5;++k){
            if(!arrive[k].empty() && pri[k]>0 && cpuT[k]>0 && pri[k]<minpri){
                minpri=pri[k];
                priT=nam[k];
            }
        }
        gant.push_back(priT);
        for(int m=0;m<5;++m){
            if(priT==nam[m])
               cpuT[m]-=1;
        }
    }
    cout<<"-----------------------------------------------------------------------------------------------------";
    cout<<endl<<"priority"<<endl;
    gantt(gant,nam,arv,ttime);

}

void RR (string nam[5],int cpuT1[5],int arv[5],int ttime){
    vector<string> gant;
    string arrive[5]={};
    queue<string> ord ; //�ϥ�queue�����ƯZ��C
    int cpuT[5];
    for(int i=0;i<5;++i)
        cpuT[i]=cpuT1[i];
    int chk=0;       //�]�w�p�ƾ��Ѽ� (q=2)
    for(int i=0;i<ttime;++i){        //for�]�C�Ӯɶ����
        for(int j=0;j<5;++j){        //�ˬd��F�ɶ�
            if(arv[j]==i){            //�p�G�Y��CPU��F�F�Npush�iqueue
                ord.push(nam[j]);
            }
        }
        for(int k=0;k<5;++k){
            if(nam[k]==ord.front() && cpuT[k]==0){   //�ˬdqueue���e�ݡA�p�G�e��CPU���ɶ���0�A
                ord.pop();                            //�N�qqueue�h��
                chk=0;                                //��p�ƾ��]��0

            }
         }
        if(chk==2){                                 //�ˬd�p�ƾ��A�p�Gq=2
            chk=0;                                  //
            ord.push(ord.front());                  //��queue���̫e��CPU�ƨ�̫᭱
            ord.pop();
        }

        for(int m=0;m<5;++m){
            if(nam[m]==ord.front() && cpuT[m]>0){  //�ˬdqueue�̫e����CPU�ɶ�
                gant.push_back(ord.front());      //�p�G�j��0�N�i�H��i�̯S�ϰ}�C
                cpuT[m]-=1;                         //CPU�ɶ�-1
                break;
            }

        }
        ++chk;                                      //�p�ƾ�+1

    }
    cout<<"-----------------------------------------------------------------------------------------------------";
    cout<<endl<<"RR(q=2)"<<endl;
    gantt(gant,nam,arv,ttime);

}
