#pragma once
#include "lexer.h"
#include "parser.h"
#include "expression.h"
#include "TAC.h"
#include <msclr/marshal_cppstd.h>
#include <vector>

namespace CompilerUI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Diagnostics;

	public ref class MyForm : public System::Windows::Forms::Form {
	public:
		MyForm(void) {
			InitializeComponent();
		}

	protected:
		~MyForm() {
			if (components) {
				delete components;
			}
		}

	private:
		System::Windows::Forms::Label^ labelInput;
		System::Windows::Forms::Label^ labelOutput;
		System::Windows::Forms::TextBox^ textBoxInput;
		System::Windows::Forms::Button^ buttonRun;
		System::Windows::Forms::TextBox^ textBoxOutput;
		System::ComponentModel::Container^ components;
		System::Windows::Forms::Button^ buttonHelp;
		System::Windows::Forms::TableLayoutPanel^ mainLayout;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void) {
			this->labelInput = (gcnew System::Windows::Forms::Label());
			this->labelOutput = (gcnew System::Windows::Forms::Label());
			this->textBoxInput = (gcnew System::Windows::Forms::TextBox());
			this->buttonRun = (gcnew System::Windows::Forms::Button());
			this->textBoxOutput = (gcnew System::Windows::Forms::TextBox());
			this->buttonHelp = (gcnew System::Windows::Forms::Button());

			// Form properties
			this->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);  // Dark background
			this->ForeColor = System::Drawing::Color::White;  // White text
			this->Font = (gcnew System::Drawing::Font("Consolas", 12));  // Consistent font across the form
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
			this->Text = L"Negs Compiler";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;

			int padding = 20;
			int labelHeight = 25;
			int spacing = 10;
			int runButtonHeight = 40;
			int width = this->ClientSize.Width - 2 * padding;
			int availableHeight = this->ClientSize.Height - 5 * spacing - 2 * labelHeight - runButtonHeight - 2 * padding;

			// Button Help (User Manual)
			this->buttonHelp->Text = L""; // Remove text for icon only
			this->buttonHelp->Size = System::Drawing::Size(70, 75); // Make it square
			this->buttonHelp->Location = System::Drawing::Point(this->ClientSize.Width - padding - 85, padding); // Shift to the left by adjusting X value
			this->buttonHelp->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
			this->buttonHelp->ForeColor = System::Drawing::Color::Black;
			this->buttonHelp->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonHelp->FlatAppearance->BorderSize = 0; // No border
			this->buttonHelp->Anchor = AnchorStyles::Top | AnchorStyles::Right;

			// Set square layout and remove round corners (square layout as per your request)
			System::Drawing::Drawing2D::GraphicsPath^ helpSquarePath = gcnew System::Drawing::Drawing2D::GraphicsPath();
			helpSquarePath->AddRectangle(System::Drawing::Rectangle(0, 0, this->buttonHelp->Width, this->buttonHelp->Height));
			this->buttonHelp->Region = gcnew System::Drawing::Region(helpSquarePath);

			// Set help icon image (resize if needed)
			System::Drawing::Image^ helpImg = System::Drawing::Image::FromFile("D:/user-guide.png");  // Make sure path is correct
			System::Drawing::Bitmap^ resizedHelpImg = gcnew System::Drawing::Bitmap(helpImg, System::Drawing::Size(70, 75)); // Resize image to fit the button
			this->buttonHelp->Image = resizedHelpImg;
			this->buttonHelp->ImageAlign = System::Drawing::ContentAlignment::MiddleCenter; // Center the image

			// Click event
			this->buttonHelp->Click += gcnew System::EventHandler(this, &MyForm::buttonHelp_Click);

			// Label: Code Editor
			this->labelInput->Text = L"Code Editor";
			this->labelInput->Size = System::Drawing::Size(200, labelHeight);  // Set size for label
			this->labelInput->Location = System::Drawing::Point(padding, padding + 40);
			this->labelInput->ForeColor = System::Drawing::Color::White;

			// TextBox Input
			this->textBoxInput->Multiline = true;
			this->textBoxInput->Location = System::Drawing::Point(padding, this->labelInput->Bottom + spacing);
			this->textBoxInput->Size = System::Drawing::Size(width, 270);  // Keep original height and width
			this->textBoxInput->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBoxInput->BackColor = System::Drawing::Color::FromArgb(50, 50, 50);
			this->textBoxInput->ForeColor = System::Drawing::Color::White;
			this->textBoxInput->Font = (gcnew System::Drawing::Font("Consolas", 16));
			this->textBoxInput->Anchor = AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right;

			// Run Button
			// Run Button
			this->buttonRun->Text = L"";
			this->buttonRun->Size = System::Drawing::Size(60, 60);
			this->buttonRun->Location = System::Drawing::Point((this->ClientSize.Width - 60) / 2, this->textBoxInput->Bottom + spacing);
			this->buttonRun->BackColor = System::Drawing::Color::Green;
			this->buttonRun->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonRun->ForeColor = System::Drawing::Color::White;
			this->buttonRun->Anchor = AnchorStyles::Top;
			this->buttonRun->FlatAppearance->BorderSize = 0;

			// Set circular shape
			System::Drawing::Drawing2D::GraphicsPath^ circlePath = gcnew System::Drawing::Drawing2D::GraphicsPath();
			circlePath->AddEllipse(0, 0, this->buttonRun->Width, this->buttonRun->Height);
			this->buttonRun->Region = gcnew System::Drawing::Region(circlePath);

			// Set image
			System::Drawing::Image^ img = System::Drawing::Image::FromFile("D:/run.png");
			System::Drawing::Bitmap^ resizedImg = gcnew System::Drawing::Bitmap(img, System::Drawing::Size(55, 55)); // Slightly smaller for padding
			this->buttonRun->Image = resizedImg;
			this->buttonRun->ImageAlign = System::Drawing::ContentAlignment::MiddleCenter;

			// Click event
			this->buttonRun->Click += gcnew System::EventHandler(this, &MyForm::buttonRun_Click);


			// Label: Output
			this->labelOutput->Text = L"Output";
			this->labelOutput->Size = System::Drawing::Size(200, labelHeight);  // Set size for label
			this->labelOutput->Location = System::Drawing::Point(padding, this->buttonRun->Bottom + spacing);
			this->labelOutput->ForeColor = System::Drawing::Color::White;

			// TextBox Output
			this->textBoxOutput->Multiline = true;
			this->textBoxOutput->Location = System::Drawing::Point(padding, this->labelOutput->Bottom + spacing);
			this->textBoxOutput->Size = System::Drawing::Size(width, 270);  // Keep original height and width
			this->textBoxOutput->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBoxOutput->BackColor = System::Drawing::Color::FromArgb(50, 50, 50);
			this->textBoxOutput->ForeColor = System::Drawing::Color::LimeGreen;
			this->textBoxOutput->Font = (gcnew System::Drawing::Font("Consolas", 16));
			this->textBoxOutput->ReadOnly = true;
			this->textBoxOutput->Anchor = AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right;

			// Add controls
			this->Controls->Add(this->labelInput);
			this->Controls->Add(this->textBoxInput);
			this->Controls->Add(this->buttonRun);
			this->Controls->Add(this->labelOutput);
			this->Controls->Add(this->textBoxOutput);
			this->Controls->Add(this->buttonHelp);

			// Change font and make the labels bold
			this->labelInput->Font = (gcnew System::Drawing::Font("Consolas", 18, System::Drawing::FontStyle::Bold));
			this->labelOutput->Font = (gcnew System::Drawing::Font("Consolas", 18, System::Drawing::FontStyle::Bold));

		}




		System::Void buttonHelp_Click(System::Object^ sender, System::EventArgs^ e) {
			System::String^ pdfPath = "D:/3rd Year/Compiler Design User Manual.pdf";

			try {
				Process::Start(pdfPath);
			}
			catch (Exception^ ex) {
				MessageBox::Show("Unable to open PDF file: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
#pragma endregion

		System::Void buttonRun_Click(System::Object^ sender, System::EventArgs^ e) {
			System::String^ userCode = textBoxInput->Text;

			msclr::interop::marshal_context context;
			std::string code = context.marshal_as<std::string>(userCode);

			std::vector<Token> tokens = tokenize(code);

			if (tokens.empty()) {
				textBoxOutput->Text = "Error: No tokens generated. Check lexer function.";
				return;
			}

			try {
				EvalResult result = ExpressionEvaluator::evaluate(code);

				System::String^ output = "Tokenizing input..." + Environment::NewLine + Environment::NewLine;
				for (const auto& token : tokens) {
					System::String^ type;
					switch (token.type) {
					case TOKEN_KEYWORD: type = "Keyword"; break;
					case TOKEN_IDENTIFIER: type = "Identifier"; break;
					case TOKEN_LITERAL: type = "Literal"; break;
					case TOKEN_DELIMITER: type = "Delimiter"; break;
					case TOKEN_COMMENT: type = "Comment"; break;
					case TOKEN_OPERATOR: type = "Operator"; break;
					case TOKEN_BRACKET: type = "Bracket"; break;
					default: type = "Unknown";
					}
					output += "[" + type + "]  " + gcnew System::String(token.value.c_str()) + Environment::NewLine;
				}

				output += Environment::NewLine + "Function Parsed Successfully!" + Environment::NewLine;

				// 🔻 TAC Logic: Check if it's an 'add' operation
				if (code.find("craft add") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("add");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft sub") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("sub");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft mul") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("mul");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft div") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("div");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft mod") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("mod");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft pow") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("pow");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft inc") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("inc");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft dec") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("dec");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft sqrt") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("sqrt");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft pyt") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("pyt");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft max") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("max");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft min") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("min");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft sqr_area") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("sqr_area");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft rect_area") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("rect_area");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft tri_area") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("tri_area");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft circle_area") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("circle_area");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft age") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("age");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft CF") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("CF");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft BMI") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("BMI");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft leapyear") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("leapyear");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft fact") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("fact");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft fib") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("fib");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft mean") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("mean");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft mode") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("mode");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft len") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("len");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft reverse") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("reverse");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}

				else if (code.find("craft concat") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("concat");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft replicate") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("replicate");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft upper") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("upper");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft lower") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("lower");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft sum") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("sum");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft abs") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("abs");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft rev_num") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("rev_num");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft armstrong") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("armstrong");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft mul_table") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("mul_table");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft sort") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("sort");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft si") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("si");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft search") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("search");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft eo") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("eo");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft count_div") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("count_div");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft swap") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("swap");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft max_arr") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("max_arr");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft min_arr") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("min_arr");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft rev_arr") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("rev_arr");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft push") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("push");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft pop") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("pop");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft sum_arr") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("sum_arr");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft gcd") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("gcd");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft lcm") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("lcm");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft to_binary") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("to_binary");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft to_decimal") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("to_decimal");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}

				else if (code.find("craft palindrom") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("palindrom");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft insert") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("insert");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft delete") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("delete");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}
				else if (code.find("craft swap") != std::string::npos) {
					std::vector<std::string> tacLines = generateTAC("swap");
					output += Environment::NewLine + "Generated Three Address Code (TAC):" + Environment::NewLine;
					for (const std::string& line : tacLines) {
						output += gcnew System::String(line.c_str()) + Environment::NewLine;
					}
				}




				//Evaluated Result logic 
				output += Environment::NewLine + "Evaluated Result: ";

				if (result.type == EvalResult::Type::Number) {
					if (std::floor(result.number) == result.number) {
						output += static_cast<int>(result.number).ToString();
					}
					else {
						output += result.number.ToString("F2");
					}
				}
				else if (result.type == EvalResult::Type::String) {
					output += gcnew System::String(result.str.c_str());
				}
				else if (result.type == EvalResult::Type::Boolean) {
					output += result.bool_value ? "true" : "false";
				}
				else if (result.type == EvalResult::Type::List) {
					output += "[";
					for (size_t i = 0; i < result.list.size(); ++i) {
						double val = result.list[i];
						if (std::floor(val) == val) {
							output += static_cast<int>(val).ToString();
						}
						else {
							output += val.ToString("F2");
						}
						if (i != result.list.size() - 1)
							output += ", ";
					}
					output += "]";
				}
				else {
					output += "Unknown result type.";
				}

				textBoxOutput->Text = output;
			}
			catch (const std::exception& ex) {
				textBoxOutput->Text = "Error: " + gcnew System::String(ex.what());
			}
		}

	};
}