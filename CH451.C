 
#include "CH451.h"
#include "Define.h"
#include "sys.h"
/*------------------------------------------------------------
��������: void ch451_write(unsigned short int command)
��������: ����ʾоƬCH451��������
��    ��: command ���͵�����
�� �� ֵ: ��
-------------------------------------------------------------*/
void ch451_write(unsigned int command)
{
  unsigned char i=0;
  LOAD_L ;
  for(i=0;i<12;i++)
  {
    if(!(command&0x01))
    {
       DAT_L;
    }
    else
    {
      DAT_H;
    }
    DCLK_L;
    command>>=1;
    DCLK_H;
  }
    LOAD_H;
}

/*-------------------------------------------------------------
��������: void ch451_init(void)
��������: CH451��ʼ������
��    ��: ��
�� �� ֵ: ��
-------------------------------------------------------------*/
  void ch451_init(void)
{
  DAT_L;
  DAT_H;
  LOAD_H;
  DCLK_H;
  ch451_write(0x0201);//оƬ�ڲ���λ
//  ch451_write(0x0202);//����˯��״̬
  ch451_write(0x0401);//�ؿ��Ź�������ʾɨ��
  ch451_write(0x0500);//�����룬ɨ�輫��8���Զ�8/16
  ch451_write(0x0600);//����˸��ʾ
}
/*-------------------------------------------------------------
��������: DISP_V(unsigned int dis_num,unsigned char point)
��������: ���������������ʾ
��    ��: dis_num��ʾ������ֵ,ʮλ��С����
�� �� ֵ: ��
-------------------------------------------------------------*/
void DISP(unsigned int dis_num,unsigned char point)
{
  unsigned char code[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};//0123456789
  unsigned int ge=0,shi=0,bai=0,qian=0;
  ge=dis_num%10;//ȡ��
  shi=(dis_num/10)%10;
  bai=(dis_num/100)%10;
  qian=dis_num/1000;
  if(qian==0)
  {
    if(bai==0)
    {
      if(shi==0)
      {
        if(!point)
        {
          shi=10;
        }
      }
      bai=10;
    }
    qian=10;
  }

    ch451_write(0x0800|code[qian]);//ǧλ
    ch451_write(0x0900|code[bai]);//��λ
    if(point==0)
    {
      ch451_write(0x0a00|code[shi]);//ʮλ
    }
    else if(point==1)
    {
      ch451_write(0x0a00|code[shi]|0x80);//ʮλ��С����
    }
    else if(point==2)
    {
         ch451_write(0x0a00|code[shi]|0x80);
    }
    ch451_write(0x0b00|code[ge]);  //��λ
}

