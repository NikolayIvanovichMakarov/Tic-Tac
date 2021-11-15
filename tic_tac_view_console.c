#include "tic_tac_types.h"

void
view_field(TIC_TAC_PIECE const * const* const g_p_fields, const size_t Y, const size_t X)
{
	size_t i,j;
	printf("-----------\n");
	for (i = 0; i < Y; ++i)
	{
		for (j = 0; j < X; ++j)
		{
			printf("%d ",g_p_fields[i][j]);
		}
		printf("\n");
	}
}