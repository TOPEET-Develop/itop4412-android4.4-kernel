/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#include <ump/ump.h>
#include <stdlib/mali_stdlib.h>

int main(int argc, char *argv[])
{
	int result = EXIT_FAILURE;

	if (UMP_OK == ump_open())
	{
		const int SZ_4KB = 4096;
		const int alloc_size = 16 * SZ_4KB;
		const int resize_1 = 1 * SZ_4KB;
		const int resize_2 = -9 * SZ_4KB;
#define  NUM_ALLOCS 128
		ump_handle h[NUM_ALLOCS];
		int i;

		for (i = 0; i < NUM_ALLOCS; i++)
		{
			h[i] = UMP_INVALID_MEMORY_HANDLE;
		}

		for (i = 0; i < NUM_ALLOCS; i++)
		{
			u8 * p;
			h[i] = ump_allocate(alloc_size, UMP_PROT_CPU_RD | UMP_PROT_CPU_WR | UMP_HINT_CPU_RD | UMP_HINT_CPU_WR | UMP_PROT_W_RD | UMP_PROT_W_WR);

			if (UMP_INVALID_MEMORY_HANDLE == h[i])
			{
				printf("Failed to allocate\n");
				break;
			}

			p = ump_map(h[i], 0, alloc_size);
			if (NULL != p)
			{
				STDLIB_MEMSET(p, 0xFF, alloc_size);
				ump_cpu_msync_now(h[i], UMP_MSYNC_CLEAN, p, alloc_size);
				ump_unmap(h[i], p, alloc_size);
			}
			else
			{
				printf("Failed to map\n");
				break;
			}
		}

		if (i == NUM_ALLOCS)
		{
			int resize_failure = 0;

			printf("%d allocations succeeded\n", NUM_ALLOCS);

			for (i = 0; i < NUM_ALLOCS; i++)
			{
				ump_secure_id check_id;

				check_id = ump_secure_id_get(h[i]);

				if (UMP_INVALID_SECURE_ID == check_id)
				{
					printf("Handle %d has an invalid secure id!\n", i);
				}
				else
				{
					int j;
					for (j = i + 1; j < NUM_ALLOCS; j++)
					{
						ump_secure_id id;
						id = ump_secure_id_get(h[j]);
						if (id == check_id)
						{
							printf("Duplicate IDs found for handles %d and %d, both have %u\n", i, j, id);
						}
					}
				}
			}

			printf("doing resize check\n");

			for (i = 0; i < NUM_ALLOCS; i++)
			{
				u64 new_size;
				ump_resize_result res;

				res = ump_resize(h[i], resize_1, &new_size);
				if (UMP_RESIZE_OK != res)
				{
					printf("resize failed with error code 0x%08X\n", res);
					resize_failure++;
				}
				else
				{
					if (new_size != (alloc_size + resize_1))
					{
						printf("Hmm, the new size isn't what I expected: %llu != %d\n", (unsigned long long)new_size, alloc_size + resize_1);
						resize_failure++;
					}
					else
					{
						int j;
						u8 * map;
						map = (u8*)ump_map(h[i], 0, new_size);
						if (NULL == map)
						{
							resize_failure++; /* record this as a resize failure */
							break;
						}
						for (j = 0; j < alloc_size; j++)
						{
							if (map[j] != 0xFF)
							{
								printf("Expected 0xFF, have 0x%02X\n", map[j]);
								resize_failure++;
							}
						}
						for (j = alloc_size; j < new_size; j++)
						{
							if (map[j] != 0)
							{
								printf("Expected 0x00, have 0x%02X\n", map[j]);
								resize_failure++;
							}
						}
						ump_unmap(h[i], map, new_size);
					}

					res = ump_resize(h[i], resize_2, &new_size);
					if (UMP_RESIZE_OK != res)
					{
						printf("resize failed with error code 0x%08x\n", res);
						resize_failure++;
					}
					else
					{
						if (new_size != (alloc_size + resize_1 + resize_2))
						{
							printf("Hmm, the new size isn't what I expected: %llu != %d\n", (unsigned long long)new_size, alloc_size + resize_1 + resize_2);
							resize_failure++;
						}
						else
						{
							int j;
							u8 * map;
							map = (u8*)ump_map(h[i], 0, new_size);
							if (NULL == map)
							{
								resize_failure++;
								break;
							}
							ump_cpu_msync_now(h[i], UMP_MSYNC_CLEAN_AND_INVALIDATE, map, new_size);
							for (j = 0; j < new_size; j++)
							{
								if (map[j] != 0xFF)
								{
									printf("expected 0xFF, have 0x%02X\n", map[j]);
									resize_failure++;
								}
							}
							ump_unmap(h[i], map, new_size);
						}
					}
				}
			}

			if (resize_failure)
			{
				printf("%d resize failures found\n", resize_failure);
			}
			else
			{
				printf("resize check OK\n");
				result = EXIT_SUCCESS;
			}
		}

		for (i = 0; i < NUM_ALLOCS; i++)
		{
			ump_release(h[i]);
		}

		ump_close();
	}

	return result;
}

