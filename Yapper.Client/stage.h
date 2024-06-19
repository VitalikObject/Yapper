#pragma once
#include "../Yapper.Shared/tcp_connection.h"

namespace Yapper::Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Yapper::Shared::Network;

	public ref class Stage : public System::Windows::Forms::Form
	{
	public:
		Stage(void);

	protected:
		~Stage();

	private:
		System::ComponentModel::Container ^components;
		void InitializeComponent(void);
		Void Stage_Load(Object^ sender, EventArgs^ e);
	};
}
