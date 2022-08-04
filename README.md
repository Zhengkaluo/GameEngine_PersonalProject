# GameEngine_PersonalProject  
Start writing a simple game engine...  
Learning from the famous Hazel Engine  

Entry point: starting the application from the engine and defined by the client  

EventDispatcher: check if event type matches the statictype if yes then handle the event (which defined from the event func), it is getting called at Application::Onevent function

binding the event call back in the setup of window at the application construction (SetEventCallBack)

EventHandle Order (credit: https://zhuanlan.zhihu.com/p/549038718):  
![image](https://github.com/Zhengkaluo/GameEngine_PersonalProject/blob/main/IMG/EventHandleOrder.jpg)