/*老師測資
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
        cout<<"請分別輸入第"<<i+1<<"個CPU名稱、CPU時間、到達時間、優先權:  ";
        cin>>nam[i]>>cpuT[i]>>arv[i]>>pri[i];
    }
    int ttime=0;
    for(int i=0;i<5;++i){
        ttime+=cpuT[i];
    }
   FCFS(nam,cpuT,arv,ttime); //呼叫FCFS
   SJF (nam,cpuT,arv,ttime);
   priority(nam,cpuT,arv,pri,ttime);
   RR(nam,cpuT,arv,ttime);
    return 0;
}

void gantt(vector<string> gant,string nam[5],int arv[5],int ttime){
    cout<<"gantt圖"<<endl;
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

    int rtime[5]={0}; //完成時間陣列
    cout<<"回復時間"<<endl;
    for(int i=ttime-1;i>=0;--i){
        for(int j=0;j<5;++j){
            if(nam[j]==gant[i]&&rtime[j]<i){
                rtime[j]=i+1;
            }
        }
    }
    for(int j=0;j<5;++j){
        cout<<nam[j]<<"="<<rtime[j]-arv[j]<<"  "; //完成時間減掉到達時間
        }
    cout<<endl;

    int wtime[5]={ttime,ttime,ttime,ttime,ttime}; //存放總等待時間(不計到達時間和結束時間)
    cout<<"等待時間"<<endl;
    for(int i=0;i<ttime;++i){
        for(int j=0;j<5;++j){
            if(nam[j]==gant[i]){
                wtime[j]-=1;
            }
        }
    }
    for(int j=0;j<5;++j){
        cout<<nam[j]<<"="<<wtime[j]-(ttime-rtime[j])-arv[j]<<"  "; //完成時間減掉到達時間
        }
    cout<<endl<<"-----------------------------------------------------------------------------------------------------"<<endl;
     gant.clear();

}

void  FCFS(string nam[5],int cpuT[5],int arv[5],int ttime){

    vector<string> gant; //存放甘特圖
    vector<string> v;
    for(int i=0;i<ttime;++i){
        for(int j=0;j<5;++j){      //比較到達時間，早到的放進去v陣列
            if(arv[j]==i){
                v.push_back(nam[j]);
            }
        }

    }
    for(int i=0;i<5;++i){
        for(int j=0;j<5;++j){       //依照v陣列的排班順序，每單位時間放進gant陣列
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
    vector<string> gant; //存放甘特圖
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
    vector<string> gant; //存放甘特圖
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
    queue<string> ord ; //使用queue紀錄排班佇列
    int cpuT[5];
    for(int i=0;i<5;++i)
        cpuT[i]=cpuT1[i];
    int chk=0;       //設定計數器參數 (q=2)
    for(int i=0;i<ttime;++i){        //for跑每個時間單位
        for(int j=0;j<5;++j){        //檢查到達時間
            if(arv[j]==i){            //如果某個CPU到達了就push進queue
                ord.push(nam[j]);
            }
        }
        for(int k=0;k<5;++k){
            if(nam[k]==ord.front() && cpuT[k]==0){   //檢查queue的前端，如果前端CPU的時間為0，
                ord.pop();                            //就從queue去掉
                chk=0;                                //把計數器設為0

            }
         }
        if(chk==2){                                 //檢查計數器，如果q=2
            chk=0;                                  //
            ord.push(ord.front());                  //把queue的最前端CPU排到最後面
            ord.pop();
        }

        for(int m=0;m<5;++m){
            if(nam[m]==ord.front() && cpuT[m]>0){  //檢查queue最前面的CPU時間
                gant.push_back(ord.front());      //如果大於0就可以放進甘特圖陣列
                cpuT[m]-=1;                         //CPU時間-1
                break;
            }

        }
        ++chk;                                      //計數器+1

    }
    cout<<"-----------------------------------------------------------------------------------------------------";
    cout<<endl<<"RR(q=2)"<<endl;
    gantt(gant,nam,arv,ttime);

}
