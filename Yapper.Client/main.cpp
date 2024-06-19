#include "stage.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace Yapper::Client;

[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Stage stage;
	Application::Run(% stage);

	return 0;
}