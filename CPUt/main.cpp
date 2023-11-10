/*老師測資
p1 10 0 4
p2 2 1 1
p3 4 3 3
p4 1 4 2
p5 5 2 5
*/
/*
測資
p1 8 1 1
p2 5 0 3
p3 2 2 5
p4 9 4 2
p5 1 3 4
*/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void FCFS(string[],int[],int[],int);   //因為function prototype關係，所以把函式原型都寫在上面方便互相呼叫
void SJF(string[],int[],int[],int);
void priority(string[],int[],int[],int[],int);
void RR(string[],int[],int[],int);
void gantt(vector<string>,string[],int[],int);

int main()
{
    string  nam[5]={};  //定義並初始化CPU名稱陣列
    int cpuT[5]={};     //定義並初始化CPU執行時間陣列
    int arv[5]={};      //定義並初始化CPU到達時間陣列
    int pri[5]={};      //定義並初始化CPU優先權陣列
    for(int i=0;i<5;++i){                                                        //分別輸入5項CPU測資
        cout<<"請分別輸入第"<<i+1<<"個CPU:  名稱、CPU時間、到達時間、優先權: ";
        cin>>nam[i]>>cpuT[i]>>arv[i]>>pri[i];
    }
    int ttime=0;  //定義總時間參數
    for(int i=0;i<5;++i){  //計算CPU總共花費時間
        ttime+=cpuT[i];
    }
    FCFS(nam,cpuT,arv,ttime); //呼叫FCFS、SJF、priority、RR 並傳入CPU名稱、CPU時間、到達時間、優先權;
    SJF (nam,cpuT,arv,ttime);
    priority(nam,cpuT,arv,pri,ttime);
    RR(nam,cpuT,arv,ttime);

    return 0;
}


void  FCFS(string nam[5],int cpuT[5],int arv[5],int ttime){     //FCFS演算
    vector<string> gant;     //定義vector容器 型別string 存放甘特圖陣列名稱gant
    vector<string> v;        //用於存放先到達的CPU

    for(int i=0;i<ttime;++i){      // 從0秒開始迭代計算
        for(int j=0;j<5;++j){      //迭代CPU
            if(arv[j]==i){          //如果到達時間符合 i
                v.push_back(nam[j]); //把符合的CPU名稱push進vector v
            }
        }

    }
    for(int i=0;i<5;++i){           //依照v陣列的順序進行迭代
        for(int j=0;j<5;++j){       //迭代CPU名稱
            if(v[i]==nam[j]){       //比對v陣列和CPU名稱必須符合，
                for(int k=0;k<cpuT[j];k++){   //迭代剛剛符合CPU名稱的時間 cpuT[j]
                    gant.push_back(nam[j]);   //把每單位時間的CPU名稱push進剛剛預設好的gantt圖陣列vector
                }
            }

        }
    }
    cout<<"-----------------------------------------------------------------------------------------------------";
    cout<<endl<<"FCFS"<<endl;
    gantt(gant,nam,arv,ttime); //呼叫gantt函式:給參數gant陣列、名稱、到達時間、總時間
}

void SJF(string nam[5],int cpuT1[5],int arv[5],int ttime){ //SJF演算
    vector<string> gant;    //定義vector容器 型別string 存放甘特圖陣列名稱gant
    string arrive[5]={};     //arrive陣列用於確定CPU是否到達
    string minT;          //存放最小時間的CPU名稱
    int cpuT[5];        //定義新CPU時間陣列
    for(int i=0;i<5;++i)    //把傳入函式的CPU時間cpuT1複製在新的cpuT陣列用於計算
        cpuT[i]=cpuT1[i];

    for(int i=0;i<ttime;++i){  // 從0秒開始迭代計算
        for(int j=0;j<5;++j){  //檢查每個CPU是否到達
            if(arv[j]==i)       //
                arrive[j]=nam[j]; //到達就放進arrive檢查陣列
        }
        int min=9999;    //設定參數檢查最小時間
        for(int k=0;k<5;++k){    //檢查每個CPU時間並找出最小的
            if(!arrive[k].empty() && cpuT[k]>0 && cpuT[k]<min){ //檢查CPU是否到達 && CPU時間大於0 && CPU時間是否小於min
                min=cpuT[k];    //把目前的最小時間放進min
                minT=nam[k];    //把目前最小時間的CPU名稱放進minT
            }
        }
        gant.push_back(minT);   //把目前最小時間的CPU名稱push進gant陣列
        for(int m=0;m<5;++m){
            if(minT==nam[m])
               cpuT[m]-=1;  // 把被push的CPU時間扣1
        }
    }

    cout<<"-----------------------------------------------------------------------------------------------------";
    cout<<endl<<"SJF"<<endl;
    gantt(gant,nam,arv,ttime); //呼叫gantt函式:給參數gant陣列、名稱、到達時間、總時間

}

void priority (string nam[5],int cpuT1[5],int arv[5],int pri[5],int ttime){ //優先權演算
    vector<string> gant; //存放甘特圖
    string arrive[5]={};  //arrive陣列用於確定CPU是否到達
    string priT;    //存放最優先的CPU名稱
    int cpuT[5];
    for(int i=0;i<5;++i) //把傳入函式的CPU時間cpuT1複製在新的cpuT陣列用於計算
        cpuT[i]=cpuT1[i];

    for(int i=0;i<ttime;++i){   // 從0秒開始迭代計算
        for(int j=0;j<5;++j){   //檢查每個CPU是否到達
            if(arv[j]==i)
                arrive[j]=nam[j]; ////到達就放進arrive檢查陣列
        }
        int minpri=9999; //設定參數檢查優先度
        for(int k=0;k<5;++k){   //檢查每個CPU優先度並找出最小的
            if(!arrive[k].empty() && pri[k]>0 && cpuT[k]>0 && pri[k]<minpri){   //檢查CPU是否到達 && CPU時間大於0 && CPU優先權是否小於minpri
                minpri=pri[k];
                priT=nam[k];
            }
        }
        gant.push_back(priT);  //把目前優先度高的CPU名稱push進gant陣列
        for(int m=0;m<5;++m){
            if(priT==nam[m])
               cpuT[m]-=1;      //把被push的CPU時間扣1
        }
    }
    cout<<"-----------------------------------------------------------------------------------------------------";
    cout<<endl<<"Priority"<<endl;
    gantt(gant,nam,arv,ttime); //呼叫gantt函式:給參數gant陣列、名稱、到達時間、總時間


}

void RR (string nam[5],int cpuT1[5],int arv[5],int ttime){ //RR(q=2)
    vector<string> gant;    //存放甘特圖
    string arrive[5]={};    //arrive陣列用於確定CPU是否到達
    queue<string> ord ;    //使用queue紀錄排班佇列
    int cpuT[5];
    for(int i=0;i<5;++i)    //把傳入函式的CPU時間cpuT1複製在新的cpuT陣列用於計算
        cpuT[i]=cpuT1[i];

    int chk=0;       //設定計數器參數從0開始 (q=2)

    for(int i=0;i<ttime;++i){        // 從0秒開始迭代計算
        for(int j=0;j<5;++j){        //檢查每個CPU是否到達
            if(arv[j]==i){            //如果某個CPU到達了就push進queue
                ord.push(nam[j]);
            }
        }
        for(int k=0;k<5;++k){
            if(nam[k]==ord.front() && cpuT[k]==0){   //檢查queue的前端比對CPU，如果前端CPU的時間為0，
                ord.pop();                            //就把queue前端pop掉
                chk=0;                                //把計數器重設為0

            }
         }
        if(chk==2){                                 //檢查計數器，如果為2
            chk=0;                                  //重設為0並且
            ord.push(ord.front());                  //把queue的最前端CPU排到最後面
            ord.pop();
        }

        for(int m=0;m<5;++m){
            if(nam[m]==ord.front() && cpuT[m]>0){  //檢查queue前端的CPU時間大於0
                gant.push_back(ord.front());      //就能放進gant陣列
                cpuT[m]-=1;                         //CPU時間-1
                break;
            }
        }
        ++chk;                                      //每單位迴圈計數器+1

    }
    cout<<"-----------------------------------------------------------------------------------------------------";
    cout<<endl<<"RR(q=2)"<<endl;
    gantt(gant,nam,arv,ttime);  //呼叫gantt函式:給參數gant陣列、名稱、到達時間、總時間

}

void gantt(vector<string> gant,string nam[5],int arv[5],int ttime){ //gantt函式 用於輸出甘特圖還有計算回復時間、等待時間
    cout<<"gantt圖"<<endl;
    cout<<"|"<<gant[0];           //輸出甘特圖的第一個分隔線(|)
    for(int i=0;i<ttime-1;++i){     //用for迭代甘特圖陣列並輸出圖形
        if(gant[i]==gant[i+1]){     //如果甘特圖陣列第i項與第i+1項相同 輸出空白
            cout<<"  ";
        }else{
            cout<<"|"<<gant[i+1];     //如果陣列第i和i+1項不同就輸出分隔線|和第i+1項的CPU名稱
        }
    }
    cout<<"|"<<endl;

    cout<<"0"<<"  ";
    for(int i=0;i<ttime-1;++i){     //用for迭代甘特圖陣列並輸出秒數
        if(gant[i]==gant[i+1]){   //如果甘特圖陣列第i項與第i+1項相同 輸出空白
            cout<<"  ";
        }else{                    //如果陣列第i和i+1項不同就輸出秒數
            if(i+1<10)             //這個if是排版空白用
            cout<<i+1<<"  ";
            else
             cout<<i+1<<" ";
        }
    }
    cout<<""<<ttime<<endl<<"----------------------------------------------------------------"<<endl; //輸出最終秒數還有分隔線

    //計算回復時間
    int rtime[5]={0}; //定義CPU完成時間陣列
    cout<<"回復時間"<<endl;
    for(int i=ttime-1;i>=0;--i){    //for迭代從gant陣列最後一項開始往前
        for(int j=0;j<5;++j){       //for迭代每種CPU
            if(nam[j]==gant[i] && rtime[j]<i){  //if判斷迭代到的nam[j](CPU名稱)與gant[i] 是否相符 && 迭代時間i > rtime陣列
                rtime[j]=i+1;                    // i迭代時間紀錄到 rtime陣列裡
            }
        }
    }
    for(int j=0;j<5;++j){
        cout<<nam[j]<<"="<<rtime[j]-arv[j]<<"  "; //輸出CPU名稱  完成時間-到達時間=回復時間
        }
    cout<<endl;

    //計算等待時間
    int wtime[5]={ttime,ttime,ttime,ttime,ttime}; //定義wtime總等待時間(不計到達時間和結束時間)
    cout<<"等待時間"<<endl;
    for(int i=0;i<ttime;++i){    //for迭代從gant陣列從第0項到最後一項
        for(int j=0;j<5;++j){      //for迭代每種CPU
            if(nam[j]==gant[i]){    //如果甘特圖陣列與CPU名稱相符
                wtime[j]-=1;         //就把等待時間-1
            }
        }
    }
    double ttwtime=0; //用於計算平均等待時間
    for(int j=0;j<5;++j){                                          //輸出每個CPU的等待時間
        cout<<nam[j]<<"="<<wtime[j]-(ttime-rtime[j])-arv[j]<<"  "; //第j個CPU等待時間 = (wtime總等待時間) - [(ttime-rtime)總時間減去回復時間] - (arv到達時間)
        ttwtime+=wtime[j]-(ttime-rtime[j])-arv[j];
        }
    cout<<endl<<"平均等待時間: "<<ttwtime/5;
    cout<<endl<<"-----------------------------------------------------------------------------------------------------"<<endl<<endl<<endl;
     gant.clear(); //清空gant的vector陣列

}
