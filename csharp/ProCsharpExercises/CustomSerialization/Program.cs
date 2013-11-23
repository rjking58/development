using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace CustomSerialization
{
    class Program
    {
        [Serializable]
        struct MyStruct2 : ISerializable
        {
            public long my_long;
            
            public MyStruct2(SerializationInfo info, StreamingContext context)
            {
                my_long = info.GetInt32("my_long");
            }
            public void GetObjectData(SerializationInfo info, StreamingContext context)
            {
                info.AddValue("my_long", my_long);
            }
        }
        [Serializable]
        struct MyStruct : ISerializable
        {
            public int my_int;
            public byte[] my_ary;
            public MyStruct2 my_s2;


            public MyStruct(SerializationInfo info, StreamingContext context)
            {
                my_ary = (byte[])info.GetValue("my_ary", typeof(byte[]));
                my_s2 = (MyStruct2)info.GetValue("my_s2", typeof(MyStruct2));
                my_int = info.GetInt32("my_int");
            }
            public void GetObjectData(SerializationInfo info, StreamingContext context)
            {
                info.AddValue("my_int", my_int);
                info.AddValue("my_ary", my_ary);
                info.AddValue("my_s2", my_s2);
            }
        }
        static void Main(string[] args)
        {
            List<MyStruct> my_list = new List<MyStruct>();

            for (int currEntry = 0; currEntry < 100000; currEntry++)
            {
                MyStruct mys = new MyStruct();
                mys.my_s2.my_long = 999;

                mys.my_int = 33;
                mys.my_ary = new byte[] { 4, 5, 6, 7 };
                my_list.Add(mys);
            }
            MemoryStream ms = new MemoryStream();
            BinaryFormatter bf = new BinaryFormatter();

            DateTime startTime = DateTime.Now;
            bf.Serialize(ms, my_list);
            ms.Position = 0;

            List<MyStruct> my_list2 = (List<MyStruct>)bf.Deserialize(ms);
            DateTime endTime = DateTime.Now;

            TimeSpan ts = new TimeSpan(endTime.Ticks - startTime.Ticks);


            Console.WriteLine("Serialize/Deserialize span:" + ts.Milliseconds);

        }
    }
}
