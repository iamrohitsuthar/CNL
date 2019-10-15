#include <bits/stdc++.h>
using namespace std;

class sender
{
	vector<bool> encodedData;
	bool  *data;
	int dataSize;
	int parityBits;
	friend class receiver;
	public:
	sender()
	{
		data = NULL;
	}

	void getInput(int );
	void generateParity(int );
	void alterBit()
	{
		int pos;
		cout<<"Enter positon of bit to alter"<<endl;
		cin>>pos;
		if(encodedData.size()>pos)
			encodedData[pos] = ! encodedData[pos];
		else
			cout<<"Invalid Position"<<endl;
	}


	vector<bool> getBitset(){return encodedData;}
	bool* getData(){return data;}

	void displayData(vector<bool> v)
	{
		cout<<setw(10)<<"Data : ";
		for( auto it = encodedData.begin() + 1 ; it != encodedData.end() ;it++ )
		{
			cout<<setw(5)<<*it;
		}
		cout<<endl;
		cout<<setw(10)<<"Index : ";
		for(int i=1;i<encodedData.size();i++)
		{
			cout<<setw(5)<<i;
		}
		cout<<"\n"<<endl;
	}

	void displayData(bool v[])
	{
		cout<<setw(10)<<"Data : ";
		for( int i = 1 ; i<dataSize ; i++ )
		{
			cout<<setw(5)<<v[i];
		}
		cout<<endl;
		cout<<setw(10)<<"Index : ";
		for(int i=1;i<dataSize;i++)
		{
			cout<<setw(5)<<i;
		}
		cout<<"\n"<<endl;
	}
};


class receiver
{
	vector<bool> encodedData;
	bool *correctData;
	int dataSize;
	int parityBits;
	bool pass;

	public:
	receiver(sender &o)
	{
		this->encodedData = o.encodedData;
		this->dataSize = o.dataSize;
		this->parityBits = o.parityBits;
		pass = true;
	}


	void checkParity(int );

	void extractData()
	{
		correctData = new bool[dataSize];
		for(int i = 0 , j = 0 , p = 0 ; i<encodedData.size() ; i++)
		{
			if(i == pow(2,p))
				p += 1;
			else
			{
				correctData[j] = encodedData[i];
				j+=1;
			}
		}
	}


	vector<bool> getBitset(){return encodedData;}
	bool* getCorrectData(){return correctData;}
	
	void displayData(vector<bool> v)
	{
		cout<<setw(10)<<"Data : ";
		for( auto it = encodedData.begin() + 1 ; it != encodedData.end() ;it++ )
		{
			cout<<setw(5)<<*it;
		}
		cout<<endl;
		cout<<setw(10)<<"Index : ";
		for(int i=1;i<encodedData.size();i++)
		{
			cout<<setw(5)<<i;
		}
		cout<<"\n"<<endl;
	}

	void displayData(bool v[],int ipType)
	{
		int temp = 0;
		char temp1;
		string bin;
		switch(ipType)
		{
			case 1:
				for(int i = dataSize -1 ,j=0 ;i > 0 ; i-- , j++)
				{
					temp += v[i]*pow(2,j);
				}
				cout<<"Received Data : "<<temp<<"\n"<<endl;
				break;

			case 2:
				for(int i = dataSize -1 ,j=0 ;i > 0 ; i-- , j++)
				{
					temp += v[i]*pow(2,j);
				}
				bin = (char)temp;
				cout<<"Received Data : "<<bin<<"\n"<<endl;
				break;

			case 3:
				bin = "";
				for(int i=1 ; i < dataSize ; i++)
				{
					bin += to_string(v[i]);
				}
				cout<<"Received Data : "<<bin<<"\n"<<endl;
				break;
		}
	}

};


void sender :: getInput(int ch)							//1 : Integer		2 : Character		3 : bitString
{
	int temp;
	int r;
	char temp1;
	string bin;
	switch(ch)
	{
		case 1:
			cout<<"\n\nEnter Input (Integer): ";
			cin>>temp;
			cout<<endl;

			while(temp!=0)
			{
				r = temp%2;
				temp /= 2;
				encodedData.push_back(r);
			}
			reverse(encodedData.begin(),encodedData.end());
			break;

		case 2:
			cout<<"\n\nEnter Input (Character): ";
			cin>>temp1;
			cout<<endl;
			
			temp = int(temp1);
			bin = bitset<7>(temp).to_string();
			for(auto it = bin.begin();it!=bin.end();it++)
			{
				encodedData.push_back(*it-48);
			}
			break;

		case 3:
			cout<<"\n\nEnter Input (bit String): ";
			cin>>bin;
			cout<<endl;

			for(auto it = bin.begin();it!=bin.end();it++)
			{
				encodedData.push_back(*it - 48);
			}
			break;
	}

	encodedData.insert(encodedData.begin(),NULL);
	
	dataSize = encodedData.size();
	data = new bool[dataSize];
	copy(encodedData.begin(),encodedData.end(),data);

	int p = 0;
	for( int i = 0 ; i < 10 ; i++ )
	{
		if( pow(2,i) >= (dataSize + i ) )
		{	
			p = i;
			break;
		}
	}
	parityBits = p;
	for(int i = 0 ; i < p ; i++)
	{
		int t = pow(2,i);
		encodedData.insert(encodedData.begin() + t , NULL);
	}
	cout<<"Entered Data : \n"<<endl;
	displayData(data);
}


void sender :: generateParity(int x)							
{
	for(int i = 0;i<parityBits;i++)
	{
		bool fl;
		if(x == 0)
			fl = false;
		else if(x == 1)
			fl = true;
		int t = pow(2,i);
		cout<<"Parity : "<<t<<"\tpos : ";
		string str = "";
		for(int j = t + 1 ; j<encodedData.size() ; j++)
		{
			if( t&j )
			{
				//cout<<" "<<j;
				str = str + " " +  to_string(j);
				if(encodedData[j] == 1)
					fl = !fl; 
			}
		}
		cout<<setw(20)<<str;
		cout<<"\tbit : "<<fl<<endl<<endl;
		encodedData[t] = fl;
	}
}


void receiver :: checkParity(int x)
{
	vector <bool> st;
	for(int i = 0;i<parityBits;i++)
	{
		bool fl;
		if(x == 0)
			fl = false;
		else if(x == 1)
			fl = true;
		int t = pow(2,i);
		cout<<"Parity : "<<t<<"\tpos : ";
		string str = "";
		for(int j = t ; j<encodedData.size() ; j++)
		{
			if( t&j )
			{
				//cout<<" "<<j;
				str = str + ' ' + to_string(j);
				if(encodedData[j] == 1)
					fl = !fl; 
			}
		}
		cout<<setw(20)<<str;
		cout<<"\tbit : "<<fl<<endl<<endl;
		st.push_back(fl);
		if(fl != 0)
		{
			pass = false;
		}
	}
	int pos = 0;
	for(int i = 0 ; i < st.size() ;i++ )
	{
		if(st[i] == 1)	
		{
			pos += pow(2,i);
		}
	}
	if(!pass)
	{
		cout<<"Error Detected \n Position : "<<pos<<endl<<endl;
		encodedData[pos] = !encodedData[pos];
		cout<<"Corrected Error\n"<<endl;
	}
	else
	{
		cout<<"Hamming pass\n"<<endl;
	}
}


int main()
{
	int ipType;

	sender ob;
	cout<<"-------------------------------------Sender Side----------------------------------------\n"<<endl;
	cout<<"-----------------Input----------------\n";
	cout<<"\nEnter Input type : \n\t1 : Integer		\n\t2 : Character		\n\t3 : bitString\n > ";
	cin>>ipType;
	cout<<endl;
	ob.getInput(ipType);				//1 : Integer		2 : Character		3 : bitString
	cout<<"-------Calculating Parity Bits--------\n"<<endl;
	ob.generateParity(1);		// x = 0 even parity     x = 1 odd parity
	ob.displayData(ob.getBitset());
	cout<<"-------------Transmission-------------\n"<<endl;
	char ch;
	cout<<"Alter Data ? y/n : ";
	cin>>ch;
	if(ch == 'y' || ch == 'Y')
		ob.alterBit();
	cout<<"---------------Data Sent--------------\n"<<endl;
	ob.displayData(ob.getBitset());
	cout<<"Transmission Complete\n"<<endl;
	cout<<"------------------------------------Receiver Side----------------------------------------\n"<<endl;
	cout<<"-------------Received data------------\n"<<endl;
	receiver r(ob);
	r.displayData(r.getBitset());
	cout<<"-------------checking Parity----------\n"<<endl;
	r.checkParity(1);			// x = 0 even parity     x = 1 odd parity
	cout<<"-------------received Data------------\n"<<endl;
	r.extractData();
	r.displayData(r.getCorrectData(),ipType);
}
