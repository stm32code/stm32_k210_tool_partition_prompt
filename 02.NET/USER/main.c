#include "git.h"


// 软件定时器设定
static Timer task1_id;
static Timer task2_id;
static Timer task3_id;
extern u8 time25ms;

// 获取全局变量
const char *topics[] = {S_TOPIC_NAME};

// 硬件初始化
void Hardware_Init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
		HZ = GB16_NUM();                                // 字数
    delay_init();                                   // 延时函数初始化
    GENERAL_TIM_Init(TIM_4, 0, 1);
    Usart1_Init(9600); // 串口1初始化为 9600
	 
 

#if OLED // OLED文件存在
    OLED_Clear();
#endif
		relay1out = 0;
		relay2out = 0;
		relay3out = 0;
  

}
// 网络初始化
void Net_Init()
{

#if OLED // OLED文件存在
    char str[50];
    OLED_Clear();
    // 写OLED内容
    sprintf(str, "-请打开WIFI热点");
    OLED_ShowCH(0, 0, (unsigned char *)str);
    sprintf(str, "-名称:%s         ", SSID);
    OLED_ShowCH(0, 2, (unsigned char *)str);
    sprintf(str, "-密码:%s         ", PASS);
    OLED_ShowCH(0, 4, (unsigned char *)str);
    sprintf(str, "-频率: 2.4 GHz   ");
    OLED_ShowCH(0, 6, (unsigned char *)str);
#endif
   
}

// 任务1
void task1(void)
{
	//1秒计算器
 	Automation_Close();
	Update_oled_massage();   // 更新OLED
	
}
// 任务2
void task2(void)
{
 char str[50];
// 设备重连
#if NETWORK_CHAEK
    if (Connect_Net == 0) {
			
#if OLED // OLED文件存在
        OLED_Clear();
        // 写OLED内容
        sprintf(str, "-请打开WIFI热点");
        OLED_ShowCH(0, 0, (unsigned char *)str);
        sprintf(str, "-名称:%s         ", SSID);
        OLED_ShowCH(0, 2, (unsigned char *)str);
        sprintf(str, "-密码:%s         ", PASS);
        OLED_ShowCH(0, 4, (unsigned char *)str);
        sprintf(str, "-频率: 2.4 GHz   ");
        OLED_ShowCH(0, 6, (unsigned char *)str);
#endif
        ESP8266_Init();          // 初始化ESP8266
   
    }
#endif
		
   
    State = ~State;
}
// 任务3
void task3(void)
{
   if (Connect_Net && Data_init.App == 0) {
        Data_init.App = 1;
   }
}
// 软件初始化
void SoftWare_Init(void)
{
    // 定时器初始化
    timer_init(&task1_id, task1, 1000, 1); // 1s执行一次
    timer_init(&task2_id, task2, 250, 1);  // 250ms执行一次
    timer_init(&task3_id, task3, 5000, 1); // 4s执行一次
 
}
// 主函数
int main(void)
{

    unsigned char *dataPtr = NULL;
    SoftWare_Init(); // 软件初始化
    Hardware_Init(); // 硬件初始化

    Net_Init(); // 网络初始
    TIM_Cmd(TIM4, ENABLE); // 使能计数器
	
		Get_Maopi(); // 归零
   	BeepNo(250);
    Get_Maopi(); // 归零
    while (1) {

        // 线程
        timer_loop(); // 定时器执行
        // 串口接收判断
        dataPtr = ESP8266_GetIPD(2);
     
}

