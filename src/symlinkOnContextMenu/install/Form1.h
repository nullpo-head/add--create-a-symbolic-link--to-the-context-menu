

#include <shlwapi.h>
#include <msclr/marshal.h>
#using <mscorlib.dll>

#pragma once



namespace install {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 �̊T�v
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: �����ɃR���X�g���N�^�[ �R�[�h��ǉ����܂�
			//
		}

	protected:
		/// <summary>
		/// �g�p���̃��\�[�X�����ׂăN���[���A�b�v���܂��B
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button2;
	protected: 

	private:
		/// <summary>
		/// �K�v�ȃf�U�C�i�[�ϐ��ł��B
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �f�U�C�i�[ �T�|�[�g�ɕK�v�ȃ��\�b�h�ł��B���̃��\�b�h�̓��e��
		/// �R�[�h �G�f�B�^�[�ŕύX���Ȃ��ł��������B
		/// </summary>
		void InitializeComponent(void)
		{
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// folderBrowserDialog1
			// 
			this->folderBrowserDialog1->HelpRequest += gcnew System::EventHandler(this, &Form1::folderBrowserDialog1_HelpRequest);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(14, 62);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(384, 19);
			this->textBox1->TabIndex = 0;
			this->textBox1->Text = L"C:\\Program Files\\symlinkoncontextmenu";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(404, 62);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(44, 21);
			this->button1->TabIndex = 1;
			this->button1->Text = L"�Q��";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoEllipsis = true;
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(409, 36);
			this->label1->TabIndex = 2;
			this->label1->Text = L"���s�t�@�C����K���ȃf�B���N�g���փR�s�[����K�v������܂��B��x�R�s�[�����t�@�C��\r\n�̏ꏊ�͕ύX���Ȃ��ł��������B�A���C���X�g�[����uninstall.exe��" 
				L"�܂��͒ǉ������E�N\r\n���b�N���̃��j���[����s���܂�";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(170, 104);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(119, 24);
			this->button2->TabIndex = 3;
			this->button2->Text = L"�C���X�g�[��";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(459, 141);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->ShowIcon = false;
			this->Text = L"�C���X�g�[��";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void folderBrowserDialog1_HelpRequest(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 System::Windows::Forms::DialogResult result = folderBrowserDialog1->ShowDialog();
				 if ( result == System::Windows::Forms::DialogResult::OK ) {
					this->textBox1->Text = this->folderBrowserDialog1->SelectedPath;
				 }
			 }
private: 
	bool BoolRegSetValue(HKEY hkResult, LPCTSTR name, LPCTSTR value) {
		return ERROR_SUCCESS == RegSetValueEx(hkResult, name, 0, REG_SZ, (LPCBYTE)value, sizeof(TCHAR) * (wcslen(value) + 1));
	}

	bool BoolRegCreateKey(HKEY hkey, LPCTSTR pass, HKEY *hkResult, DWORD *dwDisposition) {
		return ERROR_SUCCESS == RegCreateKeyEx(hkey, pass, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, hkResult, dwDisposition);
	}

	System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				using namespace System;
				using namespace System::IO;
				using namespace System::Windows::Forms;
				
				bool isInstallDirectoryCreated = false;
				String^ installPath = textBox1->Text;
				if (!Directory::Exists(installPath)) {
					try{
						Directory::CreateDirectory(installPath);
						isInstallDirectoryCreated = true;
						File::Create(installPath+"\\directory_created");
					} catch (...) {
						MessageBox::Show("�Ȃ�炩�̌����Ńf�B���N�g�����쐬�ł��܂���B�p�X���m���߂Ă��������B", "�G���[", MessageBoxButtons::OK, MessageBoxIcon::Hand);
						return;
					}
				}

				String ^exePath = Application::ExecutablePath;
				exePath = Path::GetDirectoryName(exePath);
				try {
					File::Copy(exePath + "\\symlink.exe", installPath + "\\symlink.exe", true);
					File::Copy(exePath + "\\symlinkdb.exe", installPath + "\\symlinkdb.exe", true);
					File::Copy(exePath + "\\uninstall.exe", installPath + "\\uninstall.exe", true);
				} catch (...) {
					MessageBox::Show(installPath + "\\symlink.exe", installPath + "\\symlink,exe", MessageBoxButtons::OK, MessageBoxIcon::Hand);
					MessageBox::Show(exePath + "\\symlink.exe", installPath + "\\symlink,exe", MessageBoxButtons::OK, MessageBoxIcon::Hand);
					MessageBox::Show("�Ȃ�炩�̌����ŃC���X�g�[����փt�@�C�����R�s�[�ł��܂���B�p�X���m���߂Ă��������B", "�G���[", MessageBoxButtons::OK, MessageBoxIcon::Hand);
					return;
				}	

				using namespace msclr::interop;
				marshal_context ^context = gcnew marshal_context();
				const wchar_t *symlink = context->marshal_as<const wchar_t*>("\"" + installPath + "\\symlink.exe\"%V");
				const wchar_t *symlinkdb = context->marshal_as<const wchar_t*>("\"" + installPath + "\\symlinkdb.exe\"%V");
				const wchar_t *uninstall = context->marshal_as<const wchar_t*>("\"" + installPath + "\\uninstall.exe\"" + installPath);
				
				 


				HKEY hkResult;
				DWORD dwDisposition;	
				bool result = BoolRegCreateKey(HKEY_CLASSES_ROOT, TEXT("*\\shell\\symlink"), &hkResult, &dwDisposition)
							&& BoolRegSetValue(hkResult, TEXT("MUIVerb"), TEXT("�V���{���b�N�����N�̍쐬"))
							&& BoolRegSetValue(hkResult, TEXT("SubCommands"), TEXT("newsymlink;symlinktodb;symuninstall"))
							//&& RegCloseKey(hkResult)
							&& BoolRegCreateKey(HKEY_CLASSES_ROOT, TEXT("Folder\\shell\\newsymlink"), &hkResult, &dwDisposition)
							&& BoolRegSetValue(hkResult, TEXT("MUIVerb"), TEXT("�V���{���b�N�����N�̍쐬"))
							&& BoolRegSetValue(hkResult, TEXT("SubCommands"), TEXT("newsymlink;symlinktodb;symuninstall"))
							//&& RegCloseKey(hkResult)
							&& BoolRegCreateKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell\\newsymlink"), &hkResult, &dwDisposition)
							&& BoolRegSetValue(hkResult, TEXT("MUIVerb"), TEXT("�V���{���b�N�����N�̍쐬"))
							//&& RegCloseKey(hkResult)
							&& BoolRegCreateKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell\\newsymlink\\command"), &hkResult, &dwDisposition)
							&& BoolRegSetValue(hkResult, TEXT(""), symlink)
							//&& RegCloseKey(hkResult)
							&& BoolRegCreateKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell\\symlinktodb"), &hkResult, &dwDisposition)
							&& BoolRegSetValue(hkResult, TEXT("MUIVerb"), TEXT("�t�@�C����Dropbox�ֈړ��������փV���{���b�N�����N�𒣂�"))
							//&& RegCloseKey(hkResult)
							&& BoolRegCreateKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell\\symlinktodb\\command"), &hkResult, &dwDisposition)
							&& BoolRegSetValue(hkResult, TEXT(""), symlinkdb)
							//&& RegCloseKey(hkResult)
							&& BoolRegCreateKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell\\symuninstall"), &hkResult, &dwDisposition)
							&& BoolRegSetValue(hkResult, TEXT("MUIVerb"), TEXT("���̃��j���[���폜����"))
							//&& RegCloseKey(hkResult)
							&& BoolRegCreateKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell\\symuninstall\\command"), &hkResult, &dwDisposition)
							&& BoolRegSetValue(hkResult, TEXT(""), uninstall);
							//&& RegCloseKey(hkResult);
				if( !result )
				{
					RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("*\\shell\\symlink"));
					RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("Folder\\shell\\newsymlink"));
					RegDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell\\newsymlink"));
					RegDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell\\symlinktodb"));
					RegDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell\\symuninstall"));
					if (isInstallDirectoryCreated) {
						Directory::Delete(installPath);
					} else {
						File::Delete(installPath + "\\symlink.exe");
						File::Delete(installPath + "\\symlinkdb.exe");
						File::Delete(installPath + "\\uninsall.exe");	
					}
					MessageBox::Show("���W�X�g���֏������݂ł��܂���B�C���X�g�[���𒆎~���܂��B", "�G���[", MessageBoxButtons::OK, MessageBoxIcon::Hand);
					return;
				}
				MessageBox::Show("�C���X�g�[�����I�����܂����B", "�I��", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
				this->Close();


				
			

		 }
};
}

