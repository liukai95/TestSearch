#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<map>
#define Bus_Total_Number 7
using namespace std;
class busline{                  //������busline
public:
    string station,bus_number;
    busline(string &station,string &bus_number):station(station),bus_number(bus_number) {}//���캯����ʼ�����ݳ�Ա
};
map<string,vector<busline> > List;//����һ����һά����վ���ַ������ڶ�ά����busline���ڽӱ�
map<string,bool> sign;
void Search(string SITE1,string Route,string number2,int snumber);//��������
int Plan_Total_Number;      //����ȫ�ֱ���
string start,end;
int main()
{
    int i,j,length;
    string site1,site2;
    //����·��
    string Busline[Bus_Total_Number] ={"��ɽ·-���ɽ-�з��-С����-����·С����-�μ���-��ɽ������-����·-������-��ɽ-�ֵ���-��ʨ·-�乤��-�Ƽ���-��ɽ-��ʨ��·-�Ҹ���-���۴�-������-�Ϻ�ɽׯ-����ѧԺ-����-�ܼ���-ʨ��ɽ",
                                        "���ͷ-��԰-������-�����-�ԼҶ�-����·-����¥-������-��ɽ·-˾�ſ�-������-ƽ����-������·-����-������-������-��ɽ-�ֵ���-�㲺��-׿��Ȫ-��Ȫ-Ԫ��ɽ-��Ԫ·-��ʨ��·-�Ҹ���-�����-ͼ���-���ν�-������-���ϴ�",
                                        "���Ƽ�-���·-��ƴ�-Ҷ���-��ɽ��-������-����·³��-�����-����������-���ׯ-׿��Ȫ-������-�����´�-���·-����ɽ-Ȱҵ��-��ʨ·-�乤��-�Ƽ���-��ɽ-��ʨ��·-�Ҹ���-���۴�-������-�Ϻ�ɽׯ-����ѧԺ-����-�ܼ���-ʨ��ɽ",
                                        "�л�·-˾�ſڶ�վ-����·��֬·-�侯ҽԺ-�˼�װ�ι㳡-����·С����-�μ���-��ɽ������-����·-������-��ɽ-�ֵ���-�㲺��-׿��Ȫ-���ׯ-����������-�����-����·³��-������-��ɽ��-��������-��ɽ��",
                                        "��̿�-��ɽ·-���ɽ-�з��-С����-����-������-������-��ɽ-�ֵ���-�㲺��-׿��Ȫ-���ׯ-����������-�����-����·³��-������-��ɽ��-��������-��ɽ��",
                                        "ƽ����-������·-����-����-������-������-��ɽ-�ֵ���-�㲺��-׿��Ȫ-���ׯ-����������-�����-����·³��-������-��ɽ��-Ҷ���-��ƴ�-ɭ�ֹ�԰-��¨��-��ɽ-���µ�-���ҵ�-�ŷ�-����-�ռҶ�-��ɽ-�µ�-�����-�Ͻִ�",
                                         "�䶫-�ż���-������-�����-�ƼҴ���-������-÷԰-��ɽ-��Ӿ��-����-������-�����´�-���·-����ɽ-ʡ�ʵ��У-С��ɽ-��һ·-��ɽ������-�μ���-����·С����-�侯ҽԺ-����·��֬·-˾�ſڶ�վ-������"};
    string Busname[Bus_Total_Number]={"�人����576·","�人����804·","�人����591·","�人����521·","�人����15·","�人����25·","�人����515·"};
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
    cout<<"�����������㣺";
    cin>>start;
    sign.clear();
    cout<<"����������յ㣺";
    cin>>end;
    sign[start] = 1;
    Search(start,start,"",1);
    return 0;
}
//�����������
void Search(string SITE1,string Route,string number2,int snumber)
{
    string Route_Total;
    if(Plan_Total_Number>=5) {//���5�����мƻ�
        return ;
    }
    if(SITE1==end) {
        cout<<"\n���мƻ�"<<++Plan_Total_Number<<": "<<endl<<endl<<Route<<endl<<endl;
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
                Search(site,Route+"   ("+(SITE1!=start?"����":"����")+bus_number+")"+"\n\n"+site,bus_number,snumber+1);
             }
                else
                {
                    Search(site,Route+"\n\n"+site,bus_number,snumber+1);
                }
            sign[site] = 0;
        }
    }
}


