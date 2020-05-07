#include <iostream>
#include <array>
#include <string>

#define MAX_SIZE 100			//maximum size

using namespace std;



/**
Removes any Extra Characters ( ' ' or '*' from the equation)
@param String Equation to Edit
*/
void Clean_Str(string& s)
{
	string s_new;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ' || s[i] == '*') continue;
		s_new += s[i];
	}
	s = s_new;
}

/**
Removes any Trailing "0"s & "."s from a string ending with a number
@param String to Edit
*/
void Clean_num_str(string& Eqn)
{
	while (1)
	{
		if (Eqn[Eqn.length() - 1] == '.')
		{
			Eqn = Eqn.substr(0, Eqn.length() - 1);
			return;
		}

		if (Eqn[Eqn.length() - 1] != '0' && Eqn[Eqn.length() - 1] != ' ' && Eqn[Eqn.length() - 1] != 0) return;

		Eqn = Eqn.substr(0, Eqn.length() - 1);
	}
}

/**
checks if a no. is Even (works with boolean too)
@param number (boolean) to be checked (boolean)
@return 1 if even (or false) and -1 if odd (or true)
*/
int Sign(int num)
{
	if (num % 2 == 0) return 1;
	else return -1;
}

/**
Extracts all Variable Names from the Eqns
@param Eqn to search
@param Array of names to insert found Variables
*/
void Extract_Var_Names(string Eqn, string Names[MAX_SIZE])
{
	int name_index = 0;

	for (int i = 0; i<Eqn.length(); i++)       //loops once per char
	{
		string var_name = "";
		if ((Eqn[i] >= 'A' && Eqn[i] <= 'Z') || (Eqn[i] >= 'a' && Eqn[i] <= 'z')) //enters if a name is found
		{
			for (i; i<Eqn.length(); i++)
			{
				if (Eqn[i] == '+' || Eqn[i] == '-' || Eqn[i] == '=') break;  //beaks when name ends
				var_name += Eqn[i];
			}

			int num_vars;				//finds no of variables
			for (num_vars = 0; 1; num_vars++)
				if (Names[num_vars] == "") break;

			bool exist = false;
			for (int j = 0; j < num_vars; j++)				//checks for existing var names
				if (Names[j] == var_name) exist = true;

			if (exist == false)
			{
				Names[num_vars] = var_name;
				name_index++;
			}
		}
	}

}

/**
Extracts all Numbers from the given Eqn
@param Equation
@param Array of names for Reference
@param Array of floats to insert Coefficients
@param Float to insert Constants
@param no of Eqns
*/
void Extract_Nums(string Eqn, string Names[MAX_SIZE], float Coefs[MAX_SIZE], float& Const, int num_of_Eqns)
{
	string var_name;
	string num_str;
	float num_float;

	int Equal_index;
	for (Equal_index = 0; Equal_index<Eqn.length(); Equal_index++)       //searches for the location of the "=" sign	
		if (Eqn[Equal_index] == '=') break;

	if (Equal_index > Eqn.length()) Eqn += "=0";

	int i = 0;
	while (i<Eqn.length())       //loops once per term
	{
		num_float = 0;
		num_str = "";
		var_name = "";
		bool sign = false;        // false = +ve , true = -ve

		if (Eqn[i] == '=') i++;
		if (Eqn[i] == '+') { sign = false; i++; }        //get sign
		else if (Eqn[i] == '-') { sign = true; i++; }
		if (i > Equal_index) sign = !sign;

		while ((Eqn[i] >= '0' && Eqn[i] <= '9') || Eqn[i] == '.')      //get number
		{
			num_str += Eqn[i];
			i++;
		}
		if (num_str == "") num_float = Sign(sign);
		else num_float = Sign(sign) * stof(num_str);

		while (Eqn[i] != '+' && Eqn[i] != '-' && Eqn[i] != '=')        //get name
		{
			if (i >= Eqn.length()) break;
			var_name += Eqn[i];
			i++;
		}

		//save name and coef
		if (var_name == "") Const += -1 * num_float;        //case Const
		else                                            //case normal Term
		{
			int var_index;        //finds Variable Index
			for (var_index = 0; var_index<num_of_Eqns; var_index++)
				if (Names[var_index] == var_name) break;

			Coefs[var_index] += num_float;
		}

	}

}

/**
Sort Variable Names using bubble sort
@param Array of Names to sort
@param Number of Eqns
*/
void Arrange_Names(string Names[MAX_SIZE], int num_of_vars)
{
	if (num_of_vars <= 1) return;

	for (int i = 1; i<num_of_vars; i++)
		if (Names[i] < Names[i - 1])
		{
			string temp = Names[i];
			Names[i] = Names[i - 1];
			Names[i - 1] = temp;
		}
	Arrange_Names(Names, num_of_vars - 1);
}

/**
Rewrites an Eqn in Proper Form
@param Eqn to rewrite
@param Array of Names
@param 2D Array of Constants
@param Array of Coefficients
@param Eqn number
*/
void Proper_Form(string& Eqn, string Names[MAX_SIZE], float Coefs[MAX_SIZE], float Const, int Eqn_no)
{
	string New_Eqn;

	int num_vars;				//finds no of variables
	for (num_vars = 0; 1; num_vars++)
		if (Names[num_vars] == "") break;

	for (int i = 0; i < num_vars; i++)				//loops once per variable
		if (Coefs[i] != 0)
		{
			if (Coefs[i] < 0)
			{
				if (Coefs[i] != -1)
				{
					New_Eqn += to_string(Coefs[i]);
					Clean_num_str(New_Eqn);
				}
				else New_Eqn += '-';
			}
			else
			{
				if (Coefs[i] != 1)
				{
					New_Eqn += ("+" + to_string(Coefs[i]));
					Clean_num_str(New_Eqn);
				}
				else New_Eqn += '+';
			}
			New_Eqn += Names[i];
		}

	New_Eqn += ("=" + to_string(Const));
	Clean_num_str(New_Eqn);

	int Equal_index;				//finds the "=" sign
	for (Equal_index = 0; Equal_index < Eqn.length(); Equal_index++)
		if (Eqn[Equal_index] == '=') break;

	if (New_Eqn[Equal_index + 1] == '+')				// removes any extra + signs
		New_Eqn = New_Eqn.substr(0, Equal_index + 1) + New_Eqn.substr(Equal_index + 2);
	else;
	if (New_Eqn[0] == '+') New_Eqn = New_Eqn.substr(1);

	Eqn = New_Eqn;
}

/**
Prints The 2D Matrix on the Screen
@param Matrix to be Printed
@param Number of Equations (no of rows)
@param Number of Unkowns (no of columns)
*/
void Print_Mat(float Mat[MAX_SIZE][MAX_SIZE], int in_rows, int in_colms)
{
	for (int row = 0; row<in_rows; row++)
	{
		for (int colm = 0; colm<in_colms; colm++)
			cout << Mat[row][colm] << "\t";

		cout << endl;
	}
}

/**
Calculates the Determinant of a n*n Matrix
@param a 2D n*n Array Matrix    [row][column]  or  [Equation][Variable]
@param no of Equations
@return returns the numerical value of the determinant
*/
float Determ(float input_Matrix[MAX_SIZE][MAX_SIZE], int Eqn_no)
{
	if (Eqn_no == 1) return input_Matrix[0][0];       //Special Cases first
	if (Eqn_no == 2) return ((input_Matrix[0][0] * input_Matrix[1][1]) - (input_Matrix[0][1] * input_Matrix[1][0]));

	float ans = 0;
	float new_Matrix[MAX_SIZE][MAX_SIZE];        //smaller Determinant

	for (int colm = 0; colm<Eqn_no; colm++)
	{
		for (int new_row = 1; new_row<Eqn_no; new_row++)       //create the smaller Determinant new_Matrix
			for (int new_colm = 0; new_colm<Eqn_no; new_colm++)        //"new_row=1" cancels the matrix's first row
			{
				if (new_colm == colm) continue;       //cancels the current column

				if (new_colm<colm)
					new_Matrix[new_row - 1][new_colm] = input_Matrix[new_row][new_colm];
				else
					new_Matrix[new_row - 1][new_colm - 1] = input_Matrix[new_row][new_colm];
			}

		ans += Sign(colm) * input_Matrix[0][colm] * Determ(new_Matrix, Eqn_no - 1);        //the Sign fn gives +ve or -ve signs for each column
	}

	return ans;

}



int main()
{
	// INPUT

	string Equations[MAX_SIZE];
	string Names[MAX_SIZE];

	float Coefficients[MAX_SIZE][MAX_SIZE];   //[Rows][Columns]  or  [Eqn][Var]
	float Constants[MAX_SIZE];           //[Eqn]

	start:				//this is a goto marker for the "restart" function

	cout << "Enter Number of Equations: \t";
	int num_of_Eqns;
	cin >> num_of_Eqns;       //Reads number of Eqns
	if (num_of_Eqns > MAX_SIZE)
	{
		cout << "Too many Equations!!\n\n";
		goto start;
	}

	cout << "Enter Equations: \n";
	for (int i = 0; i < num_of_Eqns; i++)        //Reads all Equations
	{
		getline(cin, Equations[i]);
		if (Equations[i] == "") i--;
		else Clean_Str(Equations[i]);
	}

	//SETUP

	for (int i = 0; i<num_of_Eqns; i++)				//Finds all Variable Names
		Extract_Var_Names(Equations[i], Names);				//loops once per Eqn

	int num_vars;				//finds no of variables
	for (num_vars = 0; 1; num_vars++)
		if (Names[num_vars] == "") break;

	Arrange_Names(Names, num_vars);

	for (int i = 0; i < num_of_Eqns; i++)				//initializes Coefficients & Constants
	{
		for (int j = 0; j < num_vars; j++)
			Coefficients[i][j] = 0;
		Constants[i] = 0;
	}

	for (int i = 0; i<num_of_Eqns; i++)        //Finds all Coefficients & Constants
		Extract_Nums(Equations[i], Names, Coefficients[i], Constants[i], num_of_Eqns);

	for (int i = 0; i < num_of_Eqns; i++)				//rewrites all Eqns in Proper Form
		Proper_Form(Equations[i], Names, Coefficients[i], Constants[i], i);


	//Questions

	cout <<endl << "Enter a Command: (\"help\" for Supported Fuctions)\n\n";
	string Command;
	while (1)
	{
		getline(cin, Command);
		if (Command == "") continue;
		if (Command == "quit" || Command == "Quit" || Command == "QUIT" || Command == "Q" || Command == "q") break;
		if (Command == "exit" || Command == "Exit" || Command == "EXIT") break;

		if (Command == "help" || Command == "Help" || Command == "HELP")
		{
			cout << "\"num_vars\":		Counts the number of variables\n";
			cout << "\"equation i\":		Prints Equation no i in Proper Form\n";
			cout << "\"column x\":		Prints Column of Coefficients of Varible x\n\n";

			cout << "\"add i j\":		Adds Eqn i to Eqn i\n";
			cout << "\"subtract i j\":		Subtracts Eqn j from Eqn i (j-i)\n";
			cout << "\"substitute x i j\":	Substitutes the variable x from Eqn i to Eqn j\n\n";

			cout << "\"D\":			Prints Crammer's Delta Matrix\n";
			cout << "\"D x\":			Prints Crammer's Delta Matrix of Variable x\n";
			cout << "\"D_value\":		Calculates the Determinant of Carmmer's Delta Matrix\n";
			cout << "\"solve\":		Solves the Eqns and Prints the Result of each variable\n\n";

			cout << "\"restart\":		Restarts the Program to enter new Equations\n";
			cout << "\"quit\" or \"exit\" :	Ends the Program\n\n";

			cout << "Note:	i & j can be any numbers from 1 to " << MAX_SIZE << "\n";
			cout << "	x can be any variable name\n\n";
		}

		else if (Command == "restart" || Command == "Restart" || Command == "RESTART")
		{
			cout << "\n\n\n";
			goto start;
		}

		//Level 1
		else if (Command == "num_vars")//done
		{
			cout << num_vars << endl;
		}

		else if (Command.substr(0, 8) == "equation" || Command.substr(0, 8) == "Equation")//done
		{
			cout << Equations[stoi(Command.substr(9)) - 1] << endl;
		}

		else if (Command.substr(0, 6) == "column" || Command.substr(0, 6) == "Column")//done
		{
			string var_name = Command.substr(7);
			int var_index;
			for (var_index = 0; var_index<num_of_Eqns; var_index++)
				if (Names[var_index] == var_name) break;

			for (int i = 0; i<num_of_Eqns; i++)
				cout << Coefficients[i][var_index] << endl;
		}

		//Level 2
		else if (Command.substr(0, 3) == "add" || Command.substr(0, 3) == "Add")//done
		{
			int num;
			for (num = 4; num < Command.length(); num++)
				if (Command[num] == ' ') break;
			int Eqn1 = stoi(Command.substr(4, num - 4)) - 1;
			int Eqn2 = stoi(Command.substr(num + 1)) - 1;

			string New_Eqn;

			for (int i = 0; i < num_vars; i++)				//loops once per variable
				if ((Coefficients[Eqn1][i] + Coefficients[Eqn2][i]) != 0)
				{
					if ((Coefficients[Eqn1][i] + Coefficients[Eqn2][i]) < 0)
					{
						if ((Coefficients[Eqn1][i] + Coefficients[Eqn2][i]) != -1)
							New_Eqn += to_string(Coefficients[Eqn1][i] + Coefficients[Eqn2][i]);
						else New_Eqn += '-';
					}
					else
					{
						if ((Coefficients[Eqn1][i] + Coefficients[Eqn2][i]) != 1)
							New_Eqn += ("+" + to_string(Coefficients[Eqn1][i] + Coefficients[Eqn2][i]));
						else New_Eqn += '+';
					}
					Clean_num_str(New_Eqn);
					New_Eqn += Names[i];
				}

			New_Eqn += ("=" + to_string(Constants[Eqn1] + Constants[Eqn2]));
			Clean_num_str(New_Eqn);

			int Equal_index;				//finds the "=" sign
			for (Equal_index = 0; Equal_index < New_Eqn.length(); Equal_index++)
				if (New_Eqn[Equal_index] == '=') break;

			if (New_Eqn[Equal_index + 1] == '+')
				New_Eqn = New_Eqn.substr(0, Equal_index + 1) + New_Eqn.substr(Equal_index + 2);				// removes any extra + signs
			if (New_Eqn[0] == '+') New_Eqn = New_Eqn.substr(1);

			cout << New_Eqn << endl;
		}

		else if (Command.substr(0, 8) == "subtract" || Command.substr(0, 8) == "Subtract")//done
		{
			int num;
			for (num = 9; num < Command.length(); num++)
				if (Command[num] == ' ') break;
			int Eqn1 = stoi(Command.substr(9, num - 9)) - 1;
			int Eqn2 = stoi(Command.substr(num + 1)) - 1;

			string New_Eqn;

			for (int i = 0; i < num_vars; i++)				//loops once per variable
				if ((Coefficients[Eqn1][i] - Coefficients[Eqn2][i]) != 0)
				{
					if ((Coefficients[Eqn1][i] - Coefficients[Eqn2][i]) < 0)
					{
						if ((Coefficients[Eqn1][i] - Coefficients[Eqn2][i]) != -1)
							New_Eqn += to_string(Coefficients[Eqn1][i] - Coefficients[Eqn2][i]);
						else New_Eqn += '-';
					}
					else
					{
						if ((Coefficients[Eqn1][i] - Coefficients[Eqn2][i]) != 1)
							New_Eqn += ("+" + to_string(Coefficients[Eqn1][i] - Coefficients[Eqn2][i]));
						else New_Eqn += '+';
					}
					Clean_num_str(New_Eqn);
					New_Eqn += Names[i];
				}

			New_Eqn += ("=" + to_string(Constants[Eqn1] - Constants[Eqn2]));
			Clean_num_str(New_Eqn);

			int Equal_index;				//finds the "=" sign
			for (Equal_index = 0; Equal_index < New_Eqn.length(); Equal_index++)
				if (New_Eqn[Equal_index] == '=') break;

			if (New_Eqn[Equal_index + 1] == '+')
				New_Eqn = New_Eqn.substr(0, Equal_index + 1) + New_Eqn.substr(Equal_index + 2);				// removes any extra + signs
			if (New_Eqn[0] == '+') New_Eqn = New_Eqn.substr(1);

			cout << New_Eqn << endl;
		}

		else if (Command.substr(0, 10) == "substitute" || Command.substr(0, 10) == "Substitute")//done
		{

			int num1, num2;
			for (num1 = 11; num1 < Command.length(); num1++)				//finds the Substiuted Variable's name
				if (Command[num1] == ' ') break;
			string sub_var = Command.substr(11, num1 - 11);

			int sub_var_index;				//finds the Substituted Variable's index
			for (sub_var_index = 0; sub_var_index < num_vars; sub_var_index++)
				if (Names[sub_var_index] == sub_var) break;

			for (num2 = num1 + 1; num2 < Command.length(); num2++)
				if (Command[num2] == ' ') break;
			int Eqn2 = stoi(Command.substr(num1 + 1, num2 - num1 - 1)) - 1;
			int Eqn1 = stoi(Command.substr(num2 + 1)) - 1;

			string New_Eqn;

			for (int i = 0; i < num_vars; i++)				//loops once per variable
				if (i != sub_var_index)
					if ((Coefficients[Eqn1][i] - Coefficients[Eqn2][i] * Coefficients[Eqn1][sub_var_index] / Coefficients[Eqn2][sub_var_index]) != 0)
					{
						if ((Constants[Eqn1] - Constants[Eqn2] * Coefficients[Eqn1][sub_var_index] / Coefficients[Eqn2][sub_var_index]) < 0)
						{
							if ((Constants[Eqn1] - Constants[Eqn2] * Coefficients[Eqn1][sub_var_index] / Coefficients[Eqn2][sub_var_index]) != -1)
								New_Eqn += to_string(Constants[Eqn1] - Constants[Eqn2] * Coefficients[Eqn1][sub_var_index] / Coefficients[Eqn2][sub_var_index]);
							else New_Eqn += '-';
						}
						else
						{
							if ((Constants[Eqn1] - Constants[Eqn2] * Coefficients[Eqn1][sub_var_index] / Coefficients[Eqn2][sub_var_index]) != 1)
								New_Eqn += ("+" + to_string(Constants[Eqn1] - Constants[Eqn2] * Coefficients[Eqn1][sub_var_index] / Coefficients[Eqn2][sub_var_index]));
							else New_Eqn += '+';
						}
						Clean_num_str(New_Eqn);
						New_Eqn += Names[i];
					}

			New_Eqn += ("=" + to_string(Constants[Eqn1] - Constants[Eqn2] * Coefficients[Eqn1][sub_var_index] / Coefficients[Eqn2][sub_var_index]));
			Clean_num_str(New_Eqn);

			int Equal_index;				//finds the "=" sign
			for (Equal_index = 0; Equal_index < New_Eqn.length(); Equal_index++)
				if (New_Eqn[Equal_index] == '=') break;

			if (New_Eqn[Equal_index + 1] == '+')
				New_Eqn = New_Eqn.substr(0, Equal_index + 1) + New_Eqn.substr(Equal_index + 2);				// removes any extra + signs
			if (New_Eqn[0] == '+') New_Eqn = New_Eqn.substr(1);

			cout << New_Eqn << endl;

		}

		//Level 3
		else if (Command == "D" || Command == "d")//done
		{
			Print_Mat(Coefficients, num_of_Eqns, num_vars);
		}

		else if (Command.substr(0, 2) == "D " || Command.substr(0, 2) == "d ")//done
		{
			string var_name = Command.substr(2);
			int var_index;
			for (var_index = 0; var_index<num_of_Eqns; var_index++)
				if (Names[var_index] == var_name) break;

			float Delta_n[MAX_SIZE][MAX_SIZE];        //Evaluating Delta_n
			for (int row = 0; row<num_of_Eqns; row++)
				for (int colm = 0; colm<num_vars; colm++)
				{
					if (colm == var_index)
						Delta_n[row][colm] = Constants[row];
					else Delta_n[row][colm] = Coefficients[row][colm];
				}
			Print_Mat(Delta_n, num_of_Eqns, num_vars);
		}

		else if (Command == "D_value")//done
		{
			if (num_of_Eqns != num_vars)
				cout << "No Solution";
			else
				cout << Determ(Coefficients, num_of_Eqns) << endl;
		}

		else if (Command == "solve" || Command == "Solve")//done
		{
			float Del = Determ(Coefficients, num_of_Eqns);
			if (Del == 0 || num_of_Eqns != num_vars)
				cout << "No Solution" << endl;
			else
				for (int var_index = 0; var_index<num_of_Eqns; var_index++)        //one Loop per Variable
				{

					float Delta_n[MAX_SIZE][MAX_SIZE];        //Evaluating Delta_n
					for (int row = 0; row<num_of_Eqns; row++)
						for (int colm = 0; colm<num_of_Eqns; colm++)
						{
							if (colm == var_index)
								Delta_n[row][colm] = Constants[row];
							else Delta_n[row][colm] = Coefficients[row][colm];
						}

					cout << Names[var_index] << "=" << Determ(Delta_n, num_of_Eqns) / Del << endl;

				}
		}

		else cout << "Unknown Command!" << endl;
	}

	return 0;
}
