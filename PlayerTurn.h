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
	using namespace std;

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
			this->SuspendLayout();
			// 
			// RollDice
			// 
			this->RollDice->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RollDice->Location = System::Drawing::Point(42, 27);
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
			this->BuildMortgage->Location = System::Drawing::Point(42, 178);
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
			this->Trade->Name = L"Trade";
			this->Trade->Size = System::Drawing::Size(492, 125);
			this->Trade->TabIndex = 2;
			this->Trade->Text = L"Trade";
			this->Trade->UseVisualStyleBackColor = true;
			// 
			// DeclareBankruptcy
			// 
			this->DeclareBankruptcy->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DeclareBankruptcy->Location = System::Drawing::Point(42, 484);
			this->DeclareBankruptcy->Name = L"DeclareBankruptcy";
			this->DeclareBankruptcy->Size = System::Drawing::Size(492, 125);
			this->DeclareBankruptcy->TabIndex = 3;
			this->DeclareBankruptcy->Text = L"Declare Bankruptcy";
			this->DeclareBankruptcy->UseVisualStyleBackColor = true;
			this->DeclareBankruptcy->Click += gcnew System::EventHandler(this, &PlayerTurn::DeclareBankruptcy_Click);
			// 
			// PlayerTurn
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(576, 715);
			this->Controls->Add(this->DeclareBankruptcy);
			this->Controls->Add(this->Trade);
			this->Controls->Add(this->BuildMortgage);
			this->Controls->Add(this->RollDice);
			this->Name = L"PlayerTurn";
			this->Text = L"Player Turn";
			this->Load += gcnew System::EventHandler(this, &PlayerTurn::PlayerTurn_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
		private: System::Void PlayerTurn_Load(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void RollDice_Click(System::Object^ sender, System::EventArgs^ e) {
			player[playerIndex].rollDice();
			checkSpace(tile, player, player[playerIndex].getPosition() - 1, player[playerIndex].getPlayerNum());
			MonopolyGameWithGUI::PlayerTurn::Close();
		}
		private: System::Void BuildMortgage_Click(System::Object^ sender, System::EventArgs^ e) {
			checkMortgage(tile, player, player[playerIndex].getPosition() - 1, player[playerIndex].getPlayerNum());
		}
		private: System::Void DeclareBankruptcy_Click(System::Object^ sender, System::EventArgs^ e) {
			if (MessageBox::Show("Player " + (playerIndex + 1) + "\n" + "Are You Sure You Want To\n"
				+ "Declare Bankruptcy?", "Bankruptcy", MessageBoxButtons::YesNo,
				MessageBoxIcon::Stop) == System::Windows::Forms::DialogResult::Yes) {
				num_bankrupt += declareBankruptcy(tile, player, player[playerIndex].getPosition() - 1, player[playerIndex].getPlayerNum());
			}
			
		}
	};
}

