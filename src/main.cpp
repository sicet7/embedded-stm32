#include <classes/sicet7/Application/Main/Main.h>
int main()
{
  SCB_CleanDCache();
  SCB_DisableDCache();
  return sicet7::Application::Main::GetInstance()->Run();
}