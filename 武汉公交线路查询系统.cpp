#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<map>
#define Bus_Total_Number 7
using namespace std;
class busline{                  //建立类busline
public:
    string station,bus_number;
    busline(string &station,string &bus_number):station(station),bus_number(bus_number) {}//构造函数初始化数据成员
};
map<string,vector<busline> > List;//建立一个第一维保存站点字符串，第二维是类busline的邻接表
map<string,bool> sign;
void Search(string SITE1,string Route,string number2,int snumber);//函数声明
int Plan_Total_Number;      //建立全局变量
string start,end;
int main()
{
    int i,j,length;
    string site1,site2;
    //保存路线
    string Busline[Bus_Total_Number] ={"中山路-凤凰山-螃蟹甲-小东门-民主路小东门-何家垅-洪山体育馆-中南路-丁字桥-洪山-街道口-珞狮路-武工大-黄家湾-马房山-珞狮南路-幸福村-北港村-傅家嘴-南湖山庄-澳新学院-壕沟-周家湾-狮子山",
                                        "余家头-杨园-四美塘-徐家棚-赵家墩-三家路-三层楼-积玉桥-中山路-司门口-汉阳门-平湖门-彭刘杨路-阅马场-傅家坡-丁字桥-洪山-街道口-广埠屯-卓刀泉-虎泉-元宝山-桂元路-珞狮南路-幸福村-文秀街-图书城-文治街-建安街-江南村",
                                        "烽火科技-烽火路-大黄村-叶麻店-关山口-新屋熊-珞喻路鲁巷-吴家湾-东湖开发区-马家庄-卓刀泉-东湖村-东湖新村-广八路-珞珈山-劝业场-珞狮路-武工大-黄家湾-马房山-珞狮南路-幸福村-北港村-傅家嘴-南湖山庄-澳新学院-壕沟-周家湾-狮子山",
                                        "中华路-司门口东站-民主路胭脂路-武警医院-宜家装饰广场-民主路小东门-何家垅-洪山体育馆-中南路-丁字桥-洪山-街道口-广埠屯-卓刀泉-马家庄-东湖开发区-吴家湾-珞喻路鲁巷-新屋熊-关山口-汽发社区-关山街",
                                        "大堤口-中山路-凤凰山-螃蟹甲-小东门-大东门-傅家坡-丁字桥-洪山-街道口-广埠屯-卓刀泉-马家庄-东湖开发区-吴家湾-珞喻路鲁巷-新屋熊-关山口-汽发社区-关山街",
                                        "平湖门-彭刘杨路-阅马场-大东门-傅家坡-丁字桥-洪山-街道口-广埠屯-卓刀泉-马家庄-东湖开发区-吴家湾-珞喻路鲁巷-新屋熊-关山口-叶麻店-大黄村-森林公园-油篓口-长山-高坡店-王家店-九峰-土桥-苏家墩-金鸡山-新店-左家岭-上街村",
                                         "武东-张家铺-龚家岭-彭家岭-黄家大湾-雁中嘴-梅园-猴山-游泳池-风光村-东湖村-东湖新村-广八路-珞珈山-省邮电干校-小洪山-八一路-洪山体育馆-何家垅-民主路小东门-武警医院-民主路胭脂路-司门口东站-汉阳门"};
    string Busname[Bus_Total_Number]={"武汉公交576路","武汉公交804路","武汉公交591路","武汉公交521路","武汉公交15路","武汉公交25路","武汉公交515路"};
    for (i=0;i<Bus_Total_Number;i++)
    {
        length=0;
        for(j = 0; j<Busline[i].size(); j++)
        {
            if(Busline[i][j]=='-')
            {
                site2 = Busline[i].substr(j-length,length);
                length = 0;
                break;
            }
            length++;
        }
        for(j++; j<Busline[i].size(); j++)
        {
            if(Busline[i][j]=='-')
            {
                site1 = Busline[i].substr(j-length,length);
                List[site2].push_back(busline(site1,Busname[i]));
                List[site1].push_back(busline(site2,Busname[i]));
                site2 = site1;
                length = -1;
            }
            ++length;
        }
        site1 = Busline[i].substr(j-length,length);
        List[site2].push_back(busline(site1,Busname[i]));
        List[site1].push_back(busline(site2,Busname[i]));
    }
    cout<<"请输入你的起点：";
    cin>>start;
    sign.clear();
    cout<<"请输入你的终点：";
    cin>>end;
    sign[start] = 1;
    Search(start,start,"",1);
    return 0;
}
//深度优先搜索
void Search(string SITE1,string Route,string number2,int snumber)
{
    string Route_Total;
    if(Plan_Total_Number>=5) {//输出5个可行计划
        return ;
    }
    if(SITE1==end) {
        cout<<"\n可行计划"<<++Plan_Total_Number<<": "<<endl<<endl<<Route<<endl<<endl;
        return ;
    }
    int i;
    string site,bus_number;
    for(i = 0; i<List[SITE1].size(); i++)
    {
        site = List[SITE1][i].station;
        bus_number = List[SITE1][i].bus_number;
        if(!sign[site])
        {
            sign[site] = 1;
            if(bus_number!=number2)
             {
                Search(site,Route+"   ("+(SITE1!=start?"换乘":"乘坐")+bus_number+")"+"\n\n"+site,bus_number,snumber+1);
             }
                else
                {
                    Search(site,Route+"\n\n"+site,bus_number,snumber+1);
                }
            sign[site] = 0;
        }
    }
}


