
#include<bits/stdc++.h>
using namespace std;

// class for RedisString Data structure
class RedisString
{
    map<string,string> mp;
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
    map<string,string> mp;
    
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
    map<string,list<string> :: iterator> mp;
    
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

// This function take key as input and return the length of the value of that key
// Time Complexity : O(1)
int RedisString::STRLEN(string key)
{
    if(mp.find(key)!=mp.end())
    return mp[key].size();
    
    return 0;
}

// This function adds the key value pair
// Time Complexity : O(1)
string RedisString::set(string key, string value)
{
    mp[key] = value;
    
    return "OK";
}

// This function return the string associated with that key
// Time Complexity : O(1)
string RedisString::get(string key)
{
    if(mp.find(key)!=mp.end())
    return mp[key];
    
    return "NULL";
}

// This function appends the given value with the associated key value
// Time Complexity : O(1)
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

// This function Push the node at the end of the list
// Time Complexity : O(1)
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

// This function Push the node at the front of the list
// Time Complexity : O(1)
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

// This function the value of the node at given index of the list
// Time Complexity : O(N) where N is the index
// Time Complexity : O(1) if N is first or last index
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
// Time Complexity : O(1)
int RedisList::LLEN()
{
    return coun;
}

// This function Pop the node from the front of the list
// Time Complexity : O(1)
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

// This function key value pair in the RedisHash
// Time Complexity : O(1)
int RedisHash::HSET(string key, string val)
{
    mp[key] = val;
    return 1;
}

// This function return the value associated with the key
// Time Complexity : O(1)
string RedisHash::HGET(string key)
{
    if(mp.find(key)!=mp.end())
    return mp[key];
    
    return "nil";
}

// This function return the number of key value pair in the RedisHash
// Time Complexity : O(1)
int RedisHash::HLEN()
{
    return mp.size();
}

// This function return the length of string associated with key in the RedisHash
// Time Complexity : O(1)
int RedisHash::HSTRLEN(string key)
{
    return mp[key].size();
}

// This function key exist or not in the RedisHash
// Time Complexity : O(1)
int RedisHash::HEXISTS(string key)
{
    if(mp.find(key)!=mp.end())
    return 1;
    
    return 0;
}

// This function check whether key exist in RedisSet or not
// Time Complexity : O(1)
int RedisSet::SISMEMBER(string key)
{
    if(mp.find(key)!=mp.end())
    return 1;
    
    else
    return 0;
}

// This function add key value pair in the RedisSet
// Time Complexity : O(1)
int RedisSet::SADD(string key)
{
 if(mp.find(key)!=mp.end())
 return 0;
 
 dq.push_front(key);
 mp[key] = dq.begin();
 
 return 1;
}

// This function remove key from the RedisSet if it exists
// Time Complexity : O(1)
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

// This function remove key from the RedisSortedSet if it exists
// Time Complexity : O(log(N)
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

// This function Add key,value pair in the RedisSortedSet 
// Time Complexity : O(log(N))
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

// This function returns the rank of particular key in RedisSortedSet
// Time Complexity : O(1)
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