//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TComboBox *ComboBox1;
	TButton *Button1;
	TLabel *Label1;
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
// ** ��� ���������� ��������� ���� �������
	TLabel *lbl [2][9]; // ������� � ������
	TEdit *edt [9][9];  // �������� �����
	// ��������� ��������� ������� ������� �������
	void __fastcall EditKeyPress(TObject *Sender, char &Key);   
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
