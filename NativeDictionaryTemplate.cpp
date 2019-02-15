#include <stdio.h>
#include <cstdlib>
#include <string.h>
//#include <list>

class NativeDictionary
{
  public:
    int slots_size;
    char** slots;
    int* values; 
	int step;

    NativeDictionary(int sz)
    {
      step = 3;
	  slots_size = sz;
      slots = new char*[slots_size];
      for(int i=0; i<slots_size; i++) slots[i] = NULL;

      values = new int[slots_size];
      for(int i=0; i<slots_size; i++) values[i] = -1;
    }

    int hashFun(char* key)
    {
		if (key == NULL)
			return -1;
		int index = 0;	 
		index = (int)key[0];
		for (int i = 1; key[i] != 0; i++)  // adder of sumbols
		{
		  index += (int)key[i];
		}
		if (index < 0) index *= -1;          // number modulus
		while (index >= slots_size)          // if larger that the size
		{
		  index /= 3;
		}
		return index;
    }

    bool is_key(char* key)
    {
		int index = hashFun(key);						//get index
		if (index == -1) 
			return false;

		for (int i = 0; i < 3; i++)						// 3 times 
		{
		  while (index <= slots_size - 1)						// table limit
		  {
			if (slots[index] != NULL)					// if slot is not empty
			{	
				if ( strcmp(key, slots[index]) == 0)	// compare
				{
					return true;						// if equal
				}
			}
			index += step;								// go to next slot  
		  }
		  index = index - slots_size;							// reaching limit			
		}

		for (int index = 0; index < slots_size; index++)		// slot by slot
		{
			if (slots[index] != NULL)					// if slot is not empty
			{	
				if ( strcmp(key, slots[index]) == 0)	// compare
				{
					return true;						// if equal
				}
			}
		}
		return false;
    }

    void put(char* key, int value)
    {	    
		int index = find(key);
		if (index != -1)
		{
			values[index] = value;
			return;
		}

		index = seekSlot(key);
		if (index == -1) 
			return;

		values[index] = value;		  
		slots[index] = key;    
    }

    int get(char* key)
    {
      int index = find(key);
	  if (index != -1)
	  {		  
		  return values[index];	
	  }	
      return -1;
    }

private:
  int seekSlot(char* value)
  {
    int index = hashFun(value);

    for (int i = 0; i < 3; i++)
    {
      while (index <= slots_size - 1)
      {
        if (slots[index] == NULL)
        {          
          return index;
        }
        index += step;
      }
      index = index - slots_size;
    }
	
    for (int i = 0; i < slots_size; i++)		// slot by slot
    {
      if (slots[i] == NULL)
      {      
        return i;
      }
    }
    return -1;
  }

  int find(char* key)
  { 
	int index = hashFun(key);						//get index
	if (index == -1) 
		return -1;

    for (int i = 0; i < 3; i++)						// 3 times 
    {
      while (index <= slots_size - 1)						// table limit
      {
		if (slots[index] != NULL)					// if slot is not empty
		{	
			if ( strcmp(key, slots[index]) == 0)	// compare
			{
				return index;						// if equal
			}
		}
        index += step;								// go to next slot  
      }
      index = index - slots_size;							// reaching limit			
    }

    for (int index = 0; index < slots_size; index++)		// slot by slot
    {
		if (slots[index] != NULL)					// if slot is not empty
		{	
			if ( strcmp(key, slots[index]) == 0)	// compare
			{
				return index;						// if equal
			}
		}
    }
    return -1;
  }
};

//==================== TEST ===================
/*
int test_NativeDictionary (NativeDictionary* item)
{
	 int test = 0;
	 item->put("key 1", 1);
	 if ( item->hashFun("key 1") != 5 ) test++;
	 item->put("key 2", 2);
	 if ( item->is_key("key 8") ) test++;
	 if ( item->get("key 8") != -1 ) test++;


	 item->put("key 4", 4);
	 item->put("key 5", 5);


	 if ( !(item->is_key("key 4")) ) test++;
	 if ( item->get("key 4") != 4 ) test++;
	 item->put("key 4", 104);
	 if ( item->get("key 4") != 104 ) test++;

	 if ( !(item->is_key("key 5")) ) test++;
	 if ( item->get("key 5") != 5 ) test++;
	 item->put("key 5", 105);
	 if ( item->get("key 5") != 105 ) test++;

	 item->put("key 3", 3);
	 item->put("key 6", 6);
	 item->put("key 7", 7);
	 item->put("key 8", 8);

	 if ( item->is_key("key 8") ) test++;
	 if ( item->get("key 8") != -1 ) test++;

	 return test;
}

int main()
{
	NativeDictionary* test_item = new NativeDictionary(6);	
	test_NativeDictionary(test_item);
	return 0;
}
*/

