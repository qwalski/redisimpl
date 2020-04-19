
#include<bits/stdc++.h>
using namespace std;

// class for RedisString Data structure
class RedisString
{
    unordered_map<string,string> mp;
    public :
        int STRLEN(string);
        string set(string,string);
        string get(string);
        int append(string,string);
};

// class for RedisList Data structure
class RedisList
{
       struct node
    {
        string data;
        struct node* next;
    };
    
    int coun = 0;
    struct node* head = NULL;
    struct node* tail = NULL;

    public :
        int RPUSH(string);
        int LPUSH(string);
        string LINDEX(int);
        int LLEN();
        string LPOP();
};

// class for RedisHash Data structure
class RedisHash
{
    unordered_map<string,string> mp;
    
    public :
        int HSET(string,string);
        string HGET(string);
        int HLEN();
        int HSTRLEN(string);
        int HEXISTS(string);
};

// class for RedisSet Data structure
class RedisSet
{
    list<string> dq;
    unordered_map<string,list<string> :: iterator> mp;
    
    public :
        
        int SISMEMBER(string);
        int SADD(string);
        int SREM(string);
};

// class for RedisSortedSet Data structure
class RedisSortedSet
{
    map<int,string> mp1;
    map<string,int> mp2;
    public :
        int ZREM(string);
        int ZADD(int,string);
        int ZRANK(string);
};

// This function take key as input and return the length of the value of that key if the key exists otherwise 0
int RedisString::STRLEN(string key)
{
    if(mp.find(key)!=mp.end())
    return mp[key].size();
    
    return 0;
}

// This function adds the key value pair and returns OK
string RedisString::set(string key, string value)
{
    mp[key] = value;
    
    return "OK";
}

// This function return the string associated with that key if the key exists ohterwise NULL
string RedisString::get(string key)
{
    if(mp.find(key)!=mp.end())
    return mp[key];
    
    return "NULL";
}

// This function appends the given value with the associated key value and returns the length of the string
int RedisString::append(string key, string val)
{
    if(mp.find(key)!=mp.end())
    {
        mp[key] = mp[key]+val;
    }
    else
    {
        mp[key]=val;
    }
    
    return STRLEN(key);
}

// This function Push the node at the end of the list and returns the len of the list
int RedisList::RPUSH(string val)
{
    if(!head)
    {
        struct node * temp = new node();
        temp->data = val;
        temp->next = NULL;
        
        head = temp;
        tail = temp;
    }
    
    else
    {
        struct node * temp = new node();
        temp->data = val;
        temp->next = NULL;
        
        tail->next = temp;
        tail = temp;
    }
    
    coun++;
    
    return coun;
}

// This function Push the node at the front of the list and returns the len of the list
int RedisList::LPUSH(string val)
{
    if(!head)
    {
        struct node * temp = new node();
        temp->data = val;
        temp->next = NULL;
        
        head = temp;
        tail = temp;
    }
    
    else
    {
        struct node * temp = new node();
        temp->data = val;
        temp->next = head;
        head = temp;
    }
    
    coun++;
    
    return coun;
}

// This function the value of the node at given index of the list otherwise nil
string RedisList::LINDEX(int index)
{
    if(index==0 || index+coun == 0)
    return head->data;
    
    else if(index == coun-1 || index+coun == coun-1)
    return tail->data;
    
    else if(index<coun || index+coun<coun)
    {
        if(index+coun<coun)
        index = index+coun;
        
        struct node* temp = head;
        
        while(temp!=NULL)
        {
            if(index==0)
            return temp->data;
            
            temp=temp->next;
            index--;
        }
    }
    else
    return "nil";
}

// This function returns length of the list
int RedisList::LLEN()
{
    return coun;
}

// This function Pop the node from the front of the list return it's value if it exist otherwise nil
string RedisList::LPOP()
{
    if(head == NULL)
    return "nil";
    
    struct node* temp = head;
    string s = temp->data;
    head = head->next;
    coun--; 
    
    free(temp);
    return s;
}

// This function key value pair in the RedisHash and return 1
int RedisHash::HSET(string key, string val)
{
    mp[key] = val;
    return 1;
}

// This function return the value associated with the key if the key exists otherwise nil
string RedisHash::HGET(string key)
{
    if(mp.find(key)!=mp.end())
    return mp[key];
    
    return "nil";
}

// This function return the number of key value pair in the RedisHash
int RedisHash::HLEN()
{
    return mp.size();
}

// This function return the length of string associated with key in the RedisHash if the key exist otherwise 0
int RedisHash::HSTRLEN(string key)
{
    if(mp.find(key)==mp.end())
    return 0;
    
    return mp[key].size();
}

// This function checks if the key exist or not in the RedisHash and return 1 if it exist otherwise 0
int RedisHash::HEXISTS(string key)
{
    if(mp.find(key)!=mp.end())
    return 1;
    
    return 0;
}

// This function check whether key exist in RedisSet or not and return 1 if the key exists otherwise 0
int RedisSet::SISMEMBER(string key)
{
    if(mp.find(key)!=mp.end())
    return 1;
    
    else
    return 0;
}

// This function add key value pair in the RedisSet and return 1 if the key does not exist otherwise 0
int RedisSet::SADD(string key)
{
 if(mp.find(key)!=mp.end())
 return 0;
 
 dq.push_front(key);
 mp[key] = dq.begin();
 
 return 1;
}

// This function remove key from the RedisSet if it exists and return 1 otherwise 0
int RedisSet::SREM(string key)
{
    if(mp.find(key)!=mp.end())
    {
        dq.erase(mp[key]);
        mp.erase(key);
        
        return 1;
    }
    
    
    return 0;
}

// This function remove key from the RedisSortedSet and return 1 if the key exists otherwise 0
int RedisSortedSet::ZREM(string key)
{
    if(mp2.find(key)==mp2.end())
    {
        return 0;
    }
    
    int val = mp2[key];
    mp1.erase(val);
    mp2.erase(key);
    
    return 1;
}

// This function Add key,value pair in the RedisSortedSet and return 1 if the key exists otherwise 0
int RedisSortedSet::ZADD(int val, string key)
{
    if(mp1.find(val)!=mp1.end())
    {
        return 0;
    }
    mp1[val] = key;
    mp2[key] = val;
    return 1;
}

// This function returns the rank of particular key in RedisSortedSet if the key exists otherwise -1
int RedisSortedSet::ZRANK(string key)
{
    if(mp2.find(key)==mp2.end())
    return -1;
    
    int val = mp2[key];
    
    return distance(mp1.begin(),mp1.find(val))+1;
}

int main()
{
    cout<<"RedisString Operations\n";
    RedisString str;
    cout<<str.set("key1","How")<<"\n";
    cout<<str.set("key2","Are")<<"\n";
    cout<<str.set("key3","You")<<"\n";
    cout<<str.get("key2")<<"\n";
    cout<<str.append("key3","?")<<"\n";
           
    cout<<"RedisList Operations\n";
   RedisList list;
   cout<<list.LPUSH("Hi")<<"\n";
   cout<<list.RPUSH("Kushdeep")<<"\n";
   cout<<list.LINDEX(-1)<<"\n";
   cout<<list.LLEN()<<"\n";
   cout<<list.LPOP()<<"\n";
    
    cout<<"RedisHash Operations\n";
    RedisHash hash;
    cout<<hash.HSET("key1","How")<<"\n";
    cout<<hash.HSET("key2","Are")<<"\n";
    cout<<hash.HSET("key3","You")<<"\n";
    cout<<hash.HEXISTS("key1")<<"\n";
    cout<<hash.HSTRLEN("key1")<<"\n";
    cout<<hash.HGET("key4")<<"\n";
    cout<<hash.HLEN()<<"\n";
    
     cout<<"RedisSet Operations\n";
     RedisSet st;
     cout<<st.SADD("kush")<<"\n";
     cout<<st.SADD("Hey")<<"\n";
     cout<<st.SREM("kush")<<"\n";
     cout<<st.SISMEMBER("kush")<<"\n";
     
    cout<<"RedisSortedSet Operations\n";
    RedisSortedSet sst;
    cout<<sst.ZADD(1,"one")<<"\n";
    cout<<sst.ZADD(2,"two")<<"\n";
    cout<<sst.ZRANK("two")<<"\n";
    cout<<sst.ZREM("one")<<"\n";
 
}
