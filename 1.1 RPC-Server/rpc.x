struct string_char
{
    string s<>;
    char c;
};

struct string_int
{
    string s<>;
    int i;
};

struct string_string
{
    string s1<>;
    string s2<>;
};

program RPCSA01PROG 
{
	version RPCSA01VERS 
	{
		char vs_servername_at(int)=1;

		int vs_strlen(string)=2;

		int vs_count_char(string_char)=3;

		string vs_first_token(string_char)=4;

		string_int vs_restandindex_bychar(string_char)=5;

		string_string vs_splitat(string_int)=6;

		void vs_increment(long)=7;

		void vs_shutdown()=8;

	} = 1;
} = 0x33221100;