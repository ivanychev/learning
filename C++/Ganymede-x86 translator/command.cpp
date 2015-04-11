
#include "exception.h"
#include "command.h"


extern ofstream strlog;
extern unsigned CODE_BEGIN;

//----------------------------------------------------------------------------------------------------------------------


bool get_double(ifstream& source, double* dest)
{
	CHECK_PTR(dest);
	unsigned char output [sizeof(double) + 1] = {0};
	static int count = 0;

	source.read((char*)output, sizeof(double) /*terminating char*/);
	
	bool cond = source.fail() | source.bad() |  source.eof();

	memcpy(dest, output, sizeof(double));

	unsigned char* p1 = (unsigned char*)(dest);					// debug part, don't worry
	unsigned char *p2 = (unsigned char*)((int)p1 + 1);
	unsigned char *p3 = (unsigned char*)((int)p2 + 1);
	unsigned char *p4 = (unsigned char*)((int)p3 + 1);
	unsigned char *p5 = (unsigned char*)((int)p4 + 1);
	unsigned char *p6 = (unsigned char*)((int)p5 + 1);
	unsigned char *p7 = (unsigned char*)((int)p6 + 1);
	unsigned char *p8 = (unsigned char*)((int)p7 + 1);

	printf("%d %lg\n",count++, *dest);

	return true;
}

//----------------------------------------------------------------------------------------------------------------------

Command::Command(ofstream& log):
	gan_length(0),
	x86_length(0),
	x86_codes(NULL),
	x86_address(0),
	gen_address(0),
	log_stream(log)
{
	CHECK_PTR(this);
	for (int i = 0; i < MAXGANCOMMAND; ++i) gan_codes[i] = 0;
};

//----------------------------------------------------------------------------------------------------------------------


Command::~Command()
{
	if (x86_codes != NULL) 
	{
		for (unsigned int i = 0; i < x86_length; ++i) x86_codes[i] = char_poison;
		delete x86_codes;
		x86_codes = NULL;
		x86_length = int_poison;
	}
	for (unsigned int i  = 0; i < gan_length; ++i) gan_codes[i] = double_poison;
	gan_length  = int_poison;
	x86_address = int_poison;
	gen_address = int_poison;

}

//----------------------------------------------------------------------------------------------------------------------


bool Command::check()
{
	bool condition = true;

	if (log_stream.is_open() == false)			condition = false;
	if (gan_length > 4)							condition = false;
	if (x86_codes == NULL && x86_length != 0)	condition = false;

	return condition;
}

//----------------------------------------------------------------------------------------------------------------------

bool Command::load_template(const Template_command& copied)
{
	gan_length = copied.ganymede_command_size;
	x86_length = copied.translation_size;

	TRY_ALLOC(x86_codes, char[x86_length + 1]);

	memcpy(x86_codes, copied.x86_translation_template, copied.translation_size);
	
	return true;
}

//----------------------------------------------------------------------------------------------------------------------


bool Command::get_command(ifstream& source)
{
	/*
	if (check() == false)
	{
		LOG_MESSAGE("Verification failed while getting new command");
		return false;
	}
	*/
	RT_ASSERT(check(), "Verification failed while getting new command");
	RT_ASSERT(source.is_open() == true, "Source file is not opened");

	CALL(get_double(source, gan_codes), "Failed to get next double value from source");

	int ganymede_command_num = (int)(*gan_codes) - CMD_NONE;

	LG_ASSERT((0 <= ganymede_command_num && ganymede_command_num <= CMD_IN - CMD_NONE), "Unknown command scanned");

	CALL(load_template(GANYMEDE_INSTRUCTIONS[ganymede_command_num]), "Failed while copying from template");
	
	for (unsigned int i = 1; i < gan_length; ++i) get_double(source, &(gan_codes[i]));

	return true;
}

//----------------------------------------------------------------------------------------------------------------------


void Command::console_print_ganymede_command() const
{
	for (unsigned int i = 0; i < gan_length; ++i) cout << gan_codes[i]<<endl;
	for (unsigned int i = 0; i < x86_length; ++i) printf("%ud:%02hhx ",i, x86_codes[i]);
	cout << "\n";
}

//--------------------------------------------------------------------
//-----------------------------Template Command------------------------
//--------------------------------------------------------------------

Template_command::Template_command(double command, unsigned int size, char* translation, unsigned int translation_length, ofstream& log):
ganymede_command(command),
ganymede_command_size(size),
log_stream(log),
translation_size(translation_length)
{
	
	TRY_ALLOC(x86_translation_template, char[translation_size]);

	translation_size = translation_length;

	memcpy(x86_translation_template, translation, translation_size);
}

//----------------------------------------------------------------------------------------------------------------------


Template_command::~Template_command()
{
	if (x86_translation_template != NULL) 
	{
		for (unsigned int i = 0; i < translation_size; ++i)
			x86_translation_template[i] = char_poison;
		delete x86_translation_template;
		x86_translation_template = NULL;
	}

	ganymede_command =		double_poison;
	ganymede_command_size = int_poison;
	translation_size =		int_poison;

}

//----------------------------------------------------------------------------------------------------------------------


void Template_command::console_dump() const
{
	cout	<< "I'm template of " << ganymede_command << "\nSize: " << ganymede_command_size  << endl
			<< "x86 size: " << translation_size << endl
			<< "Template:" << endl;

	for (unsigned int i = 0; i < translation_size; ++i)
	{
		if (i % 10 == 0) putchar('\n');
		printf("%02hhx ", x86_translation_template[i]);
	};

	cout	<< "End of dump\n" << endl;
}

//----------------------------------------------------------------------------------------------------------------------


void Command::print_x86(ostream& str) const
{
	if (x86_codes == NULL) str <<"NULL";
	else for (unsigned i = 0; i < x86_length; ++i) 
	{
		if (i % 5 == 0) str << "\n";
		printf("%02hhx\t", x86_codes[i]);
	}
}