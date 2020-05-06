#include <iostream>
#include <array>
#include <string>

using namespace std;



/**
checks if a no. is Even (works with boolean too)
@param number (boolean) to be checked (boolean)
@return 1 if even (or false) and -1 if odd (or true)
*/
int Sign(int num)//done
{
	if (num % 2 == 0) return 1;
	else return -1;
}

/**
Extracts all Variable Names from the Eqns
@param Eqn to search
@param Array of names to insert found Variables
*/
void Extract_Var_Names(string Eqn, string Names[100])//done
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
void Extract_Nums(string Eqn, string Names[100], float Coefs[100], float& Const, int num_of_Eqns)//done
{
	bool sign = false;        // false = +ve , true = -ve

	string var_name;
	string num_str;
	float num_float;

	int Equal_index;
	for (Equal_index = 0; Equal_index<Eqn.length(); Equal_index++)       //searches for the location of the "=" sign	//error
		if (Eqn[Equal_index] == '=') break;

	int i = 0;
	while (i<Eqn.length())       //loops once per term
	{
		num_float = 0;
		num_str = "";
		var_name = "";

		if (Eqn[i] == '+' || Eqn[i] == '=') { sign = false; i++; }        //get sign
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
Sort Variable Names
@param Array of Names to sort
@param Number of Eqns
*/
void Arrange_Names(string Names[100], int num_of_vars)//done
{
	if (num_of_vars <= 1) return;

	for(int i=1; i<num_of_vars; i++)
		if (Names[i] < Names[i - 1])
		{
			string temp = Names[i];
			Names[i] = Names[i - 1];
			Names[i - 1] = temp;
		}
	Arrange_Names(Names, num_of_vars -1);
}

/**
	Rewrites an Eqn in Proper Form
	@param Eqn to rewrite
	@param Array of Names
	@param 2D Array of Constants
	@param Array of Coefficients
	@param Eqn number
*/
void Proper_Form(string& Eqn, string Names[100], float Coefs[100], float Const,int Eqn_no)//done
{
	string New_Eqn;

	int num_vars;				//finds no of variables
	for (num_vars = 0; 1; num_vars++)
		if (Names[num_vars] == "") break;

	for (int i = 0; i < num_vars; i++)				//loops once per variable
		if (Coefs[i] != 0)
		{
			if (Coefs < 0) New_Eqn += (to_string(Coefs[i]) + Names[i]);
			else New_Eqn += ("+" + to_string(Coefs[i]) + Names[i]);
		}

	New_Eqn += ( "=" + to_string(Const));

	int Equal_index;				//finds the "=" sign
	for (Equal_index = 0; Equal_index < Eqn.length(); Equal_index++)
		if (Eqn[Equal_index] == '=') break;

	if (New_Eqn[Equal_index + 1] == '+')
    New_Eqn = New_Eqn.substr(0, Equal_index + 1) + New_Eqn.substr(Equal_index + 2);				// removes any extra + signs
	if (New_Eqn[0] == '+') New_Eqn = New_Eqn.substr(1);

	Eqn = New_Eqn;
}

/**
Prints The 2D Matrix on the Screen
@param Matrix to be Printed
@param No of Eqns for Reference (Dimension)
*/
void Print_Mat(float Mat[100][100], int Dim)//done
{
	for (int row = 0; row<Dim; row++)
	{
		for (int colm = 0; colm<Dim; colm++)
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
float Determ(float input_Matrix[100][100], int Eqn_no)//done
{
	if (Eqn_no == 1) return input_Matrix[0][0];       //Special Cases first
	if (Eqn_no == 2) return ((input_Matrix[0][0] * input_Matrix[1][1]) - (input_Matrix[0][1] * input_Matrix[1][0]));

	float ans = 0;
	float new_Matrix[100][100];        //smaller Determinant

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



int main()//remaining substitution
{
	// INPUT

	string Equations[100];
	string Names[100];

	float Coefficients[100][100];   //[Rows][Columns]  or  [Eqn][Var]
	float Constants[100];           //[Eqn]

	int num_of_Eqns;
	cin >> num_of_Eqns;       //Reads number of Eqns

	for (int i=0; i < num_of_Eqns; i++)        //Reads all Equations
	{
		cin >> Equations[i];
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
		Proper_Form(Equations[i], Names, Coefficients[i], Constants[i],i);


	//Questions

	string Command;
	while (1)
	{
		getline(cin, Command);
		if (Command == "") continue;
		if (Command == "quit") break;

		//Level 1 done & checked
		else if (Command == "num_vars")//done
		{
			int num_vars;
			for (num_vars = 0; 1; num_vars++)
				if (Names[num_vars] == "") break;
			cout << num_vars <<endl;
		}

		else if (Command.substr(0, 8) == "equation")//done
		{
			int Eqn_no = stoi(Command.substr(9)) - 1;

			cout << Equations[Eqn_no] <<endl;
		}

		else if (Command.substr(0, 6) == "column")//done
		{
			string var_name = Command.substr(7);
			int var_index;
			for (var_index = 0; var_index<num_of_Eqns; var_index++)
				if (Names[var_index] == var_name) break;

			for (int i = 0; i<num_of_Eqns; i++)
				cout << Coefficients[i][var_index] << endl;
		}

		//Level 2
		else if (Command.substr(0, 3) == "add")//done
		{
			int num;
			for (num = 4; num < Command.length(); num++)
				if (Command[num] == ' ') break;
			int Eqn1 = stoi(Command.substr(4,num-4))-1;
			int Eqn2 = stoi(Command.substr(num+1))-1;

			string New_Eqn;

			for (int i = 0; i < num_vars; i++)				//loops once per variable
				if ((Coefficients[Eqn1][i] + Coefficients[Eqn2][i]) != 0)
				{
					if ((Coefficients[Eqn1][i] - Coefficients[Eqn2][i]) < 0)
						New_Eqn += (to_string((Coefficients[Eqn1][i] + Coefficients[Eqn2][i])) + Names[i]);
					else New_Eqn += ("+" + to_string((Coefficients[Eqn1][i] + Coefficients[Eqn2][i])) + Names[i]);
				}

			New_Eqn += ("=" + to_string(Constants[Eqn1] + Constants[Eqn2]));

			int Equal_index;				//finds the "=" sign
			for (Equal_index = 0; Equal_index < New_Eqn.length(); Equal_index++)
				if (New_Eqn[Equal_index] == '=') break;

			if (New_Eqn[Equal_index + 1] == '+')
				New_Eqn = New_Eqn.substr(0, Equal_index + 1) + New_Eqn.substr(Equal_index + 2);				// removes any extra + signs
			if (New_Eqn[0] == '+') New_Eqn = New_Eqn.substr(1);

			cout << New_Eqn <<endl;
		}

		else if (Command.substr(0, 8) == "subtract")//done
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
						New_Eqn += (to_string((Coefficients[Eqn1][i] - Coefficients[Eqn2][i])) + Names[i]);
					else New_Eqn += ("+" + to_string((Coefficients[Eqn1][i] - Coefficients[Eqn2][i])) + Names[i]);
				}

			New_Eqn += ("=" + to_string(Constants[Eqn1] - Constants[Eqn2]));

			int Equal_index;				//finds the "=" sign
			for (Equal_index = 0; Equal_index < New_Eqn.length(); Equal_index++)
				if (New_Eqn[Equal_index] == '=') break;

			if (New_Eqn[Equal_index + 1] == '+')
				New_Eqn = New_Eqn.substr(0, Equal_index + 1) + New_Eqn.substr(Equal_index + 2);				// removes any extra + signs
			if (New_Eqn[0] == '+') New_Eqn = New_Eqn.substr(1);

			cout << New_Eqn << endl;
		}

		else if (Command.substr(0, 10) == "substitute")
		{

		}

		//Level 3 done & checked
		else if (Command == "D")//done
		{
			Print_Mat(Coefficients, num_of_Eqns);
		}

		else if (Command.substr(0, 2) == "D ")//done
		{
			string var_name = Command.substr(2);
			int var_index;
			for (var_index = 0; var_index<num_of_Eqns; var_index++)
				if (Names[var_index] == var_name) break;

			float Delta_n[100][100];        //Evaluating Delta_n
			for (int row = 0; row<num_of_Eqns; row++)
				for (int colm = 0; colm<num_of_Eqns; colm++)
				{
					if (colm == var_index)
						Delta_n[row][colm] = Constants[row];
					else Delta_n[row][colm] = Coefficients[row][colm];
				}
			Print_Mat(Delta_n, num_of_Eqns);
		}

		else if (Command == "D_value")//done
		{
			cout << Determ(Coefficients, num_of_Eqns) <<endl;
		}

		else if (Command == "solve")//done
		{
			for (int var_index = 0; var_index<num_of_Eqns; var_index++)        //one Loop per Variable
			{
				float Delta_n[100][100];        //Evaluating Delta_n
				for (int row = 0; row<num_of_Eqns; row++)
					for (int colm = 0; colm<num_of_Eqns; colm++)
					{
						if (colm == var_index)
							Delta_n[row][colm] = Constants[row];
						else Delta_n[row][colm] = Coefficients[row][colm];
					}

				cout << Names[var_index] << "=" << Determ(Delta_n, num_of_Eqns) / Determ(Coefficients, num_of_Eqns) << endl;
			}
		}

		else cout << "Unknown Command!" << endl;
	}

	return 0;
}
