#include "git.h"


// �����ʱ���趨
static Timer task1_id;
static Timer task2_id;
static Timer task3_id;
extern u8 time25ms;

// ��ȡȫ�ֱ���
const char *topics[] = {S_TOPIC_NAME};

// Ӳ����ʼ��
void Hardware_Init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // �����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
		HZ = GB16_NUM();                                // ����
    delay_init();                                   // ��ʱ������ʼ��
    GENERAL_TIM_Init(TIM_4, 0, 1);
    Usart1_Init(9600); // ����1��ʼ��Ϊ 9600
	 
 

#if OLED // OLED�ļ�����
    OLED_Clear();
#endif
		relay1out = 0;
		relay2out = 0;
		relay3out = 0;
  

}
// �����ʼ��
void Net_Init()
{

#if OLED // OLED�ļ�����
    char str[50];
    OLED_Clear();
    // дOLED����
    sprintf(str, "-���WIFI�ȵ�");
    OLED_ShowCH(0, 0, (unsigned char *)str);
    sprintf(str, "-����:%s         ", SSID);
    OLED_ShowCH(0, 2, (unsigned char *)str);
    sprintf(str, "-����:%s         ", PASS);
    OLED_ShowCH(0, 4, (unsigned char *)str);
    sprintf(str, "-Ƶ��: 2.4 GHz   ");
    OLED_ShowCH(0, 6, (unsigned char *)str);
#endif
   
}

// ����1
void task1(void)
{
	//1�������
 	Automation_Close();
	Update_oled_massage();   // ����OLED
	
}
// ����2
void task2(void)
{
 char str[50];
// �豸����
#if NETWORK_CHAEK
    if (Connect_Net == 0) {
			
#if OLED // OLED�ļ�����
        OLED_Clear();
        // дOLED����
        sprintf(str, "-���WIFI�ȵ�");
        OLED_ShowCH(0, 0, (unsigned char *)str);
        sprintf(str, "-����:%s         ", SSID);
        OLED_ShowCH(0, 2, (unsigned char *)str);
        sprintf(str, "-����:%s         ", PASS);
        OLED_ShowCH(0, 4, (unsigned char *)str);
        sprintf(str, "-Ƶ��: 2.4 GHz   ");
        OLED_ShowCH(0, 6, (unsigned char *)str);
#endif
        ESP8266_Init();          // ��ʼ��ESP8266
   
    }
#endif
		
   
    State = ~State;
}
// ����3
void task3(void)
{
   if (Connect_Net && Data_init.App == 0) {
        Data_init.App = 1;
   }
}
// �����ʼ��
void SoftWare_Init(void)
{
    // ��ʱ����ʼ��
    timer_init(&task1_id, task1, 1000, 1); // 1sִ��һ��
    timer_init(&task2_id, task2, 250, 1);  // 250msִ��һ��
    timer_init(&task3_id, task3, 5000, 1); // 4sִ��һ��
 
}
// ������
int main(void)
{

    unsigned char *dataPtr = NULL;
    SoftWare_Init(); // �����ʼ��
    Hardware_Init(); // Ӳ����ʼ��

    Net_Init(); // �����ʼ
    TIM_Cmd(TIM4, ENABLE); // ʹ�ܼ�����
	
		Get_Maopi(); // ����
   	BeepNo(250);
    Get_Maopi(); // ����
    while (1) {

        // �߳�
        timer_loop(); // ��ʱ��ִ��
        // ���ڽ����ж�
        dataPtr = ESP8266_GetIPD(2);
     
}

