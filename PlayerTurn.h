#pragma once

#include "Functions.h"
#include <Windows.h>
#include <iostream>

namespace MonopolyGameWithGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	

	/// <summary>
	/// Summary for PlayerTurn
	/// </summary>
	public ref class PlayerTurn : public System::Windows::Forms::Form
	{
	public:
		PlayerTurn(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PlayerTurn()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ RollDice;
	protected:
	private: System::Windows::Forms::Button^ BuildMortgage;
	private: System::Windows::Forms::Button^ Trade;
	private: System::Windows::Forms::Button^ DeclareBankruptcy;
	private: System::Windows::Forms::Label^ Player1;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->RollDice = (gcnew System::Windows::Forms::Button());
			this->BuildMortgage = (gcnew System::Windows::Forms::Button());
			this->Trade = (gcnew System::Windows::Forms::Button());
			this->DeclareBankruptcy = (gcnew System::Windows::Forms::Button());
			this->Player1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// RollDice
			// 
			this->RollDice->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RollDice->Location = System::Drawing::Point(42, 27);
			this->RollDice->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->RollDice->Name = L"RollDice";
			this->RollDice->Size = System::Drawing::Size(492, 125);
			this->RollDice->TabIndex = 0;
			this->RollDice->Text = L"Roll Dice";
			this->RollDice->UseVisualStyleBackColor = true;
			this->RollDice->Click += gcnew System::EventHandler(this, &PlayerTurn::RollDice_Click);
			// 
			// BuildMortgage
			// 
			this->BuildMortgage->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BuildMortgage->Location = System::Drawing::Point(42, 179);
			this->BuildMortgage->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->BuildMortgage->Name = L"BuildMortgage";
			this->BuildMortgage->Size = System::Drawing::Size(492, 125);
			this->BuildMortgage->TabIndex = 1;
			this->BuildMortgage->Text = L"Build/Mortgage";
			this->BuildMortgage->UseVisualStyleBackColor = true;
			this->BuildMortgage->Click += gcnew System::EventHandler(this, &PlayerTurn::BuildMortgage_Click);
			// 
			// Trade
			// 
			this->Trade->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Trade->Location = System::Drawing::Point(42, 329);
			this->Trade->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Trade->Name = L"Trade";
			this->Trade->Size = System::Drawing::Size(492, 125);
			this->Trade->TabIndex = 2;
			this->Trade->Text = L"Trade";
			this->Trade->UseVisualStyleBackColor = true;
			this->Trade->Click += gcnew System::EventHandler(this, &PlayerTurn::Trade_Click);
			// 
			// DeclareBankruptcy
			// 
			this->DeclareBankruptcy->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DeclareBankruptcy->Location = System::Drawing::Point(42, 485);
			this->DeclareBankruptcy->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->DeclareBankruptcy->Name = L"DeclareBankruptcy";
			this->DeclareBankruptcy->Size = System::Drawing::Size(492, 125);
			this->DeclareBankruptcy->TabIndex = 3;
			this->DeclareBankruptcy->Text = L"Declare Bankruptcy";
			this->DeclareBankruptcy->UseVisualStyleBackColor = true;
			this->DeclareBankruptcy->Click += gcnew System::EventHandler(this, &PlayerTurn::DeclareBankruptcy_Click);
			// 
			// Player1
			// 
			this->Player1->AutoSize = true;
			this->Player1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 17.5F));
			this->Player1->Location = System::Drawing::Point(644, 65);
			this->Player1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->Player1->Name = L"Player1";
			this->Player1->Size = System::Drawing::Size(147, 54);
			this->Player1->TabIndex = 4;
			this->Player1->Text = L"label1";
			// 
			// PlayerTurn
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1232, 715);
			this->Controls->Add(this->Player1);
			this->Controls->Add(this->DeclareBankruptcy);
			this->Controls->Add(this->Trade);
			this->Controls->Add(this->BuildMortgage);
			this->Controls->Add(this->RollDice);
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"PlayerTurn";
			this->Text = L"Player Turn";
			this->Load += gcnew System::EventHandler(this, &PlayerTurn::PlayerTurn_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: System::Void PlayerTurn_Load(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void RollDice_Click(System::Object^ sender, System::EventArgs^ e) {
			string temp = "Pickles";
			//Player1->Text = temp;
			
			MonopolyGameWithGUI::PlayerTurn::Close();
			setLabel();
			player[playerIndex].rollDice();
			checkSpace(tile, player, player[playerIndex].getPosition() - 1, player[playerIndex].getPlayerNum());
		}
		private: System::Void BuildMortgage_Click(System::Object^ sender, System::EventArgs^ e) {
			checkMortgage(tile, player, player[playerIndex].getPosition() - 1, player[playerIndex].getPlayerNum());
		}
		private: System::Void DeclareBankruptcy_Click(System::Object^ sender, System::EventArgs^ e) {
			if (MessageBox::Show("Player " + (playerIndex + 1) + "\n" + "Are You Sure You Want To\n"
				+ "Declare Bankruptcy?", "Bankruptcy", MessageBoxButtons::YesNo,
				MessageBoxIcon::Stop) == System::Windows::Forms::DialogResult::Yes) {
				MonopolyGameWithGUI::PlayerTurn::Close();
				num_bankrupt += declareBankruptcy(tile, player, player[playerIndex].getPosition() - 1, player[playerIndex].getPlayerNum());
			}
			
		}
		private: System::Void Trade_Click(System::Object^ sender, System::EventArgs^ e) {
			initializeTrade(tile, player, player[playerIndex].getPlayerNum());
		}
		public:
			void setLabel() {
				
				Player1->Text = "This works";
			}
	
	};
}

