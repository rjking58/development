

class OLC
{

public:
	void Exec (long a_long)
	{
		return 1L;
	}
	long Exec (long a_long)
	{
		return a_long + 10L;
	}
};


main(void )

{

	OLC olc_obj;

	olc_obj.Exec(20L);
}