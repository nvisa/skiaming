// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// indexedproperty.cs
using System;

public class Document
{
    // 以下类型允许以类似字数组的方式查看文档:
    public class WordCollection
    {
        readonly Document document;  // 包含文档

        internal WordCollection(Document d)
        {
           document = d;
        }

        // Helper 函数 -- 从字符“begin”开始在字符数组“text”中搜索
        // 字数“wordCount”。如果少于 
        // wordCount 字数，则返回 false。将“start”和
        // “length”设置为文本中字的位置和长度:
        private bool GetWord(char[] text, int begin, int wordCount, 
                                       out int start, out int length) 
        { 
            int end = text.Length;
            int count = 0;
            int inWord = -1;
            start = length = 0; 

            for (int i = begin; i <= end; ++i) 
            {
                bool isLetter = i < end && Char.IsLetterOrDigit(text[i]);

                if (inWord >= 0) 
                {
                    if (!isLetter) 
                    {
                        if (count++ == wordCount) 
                        {
                            start = inWord;
                            length = i - inWord;
                            return true;
                        }
                        inWord = -1;
                    }
                }
                else 
                {
                    if (isLetter)
                        inWord = i;
                }
            }
            return false;
        }

        // 获取和设置包含文档中的字的索引器:
        public string this[int index] 
        {
            get 
            { 
                int start, length;
                if (GetWord(document.TextArray, 0, index, out start, 
                                                          out length))
                    return new string(document.TextArray, start, length);
                else
                    throw new IndexOutOfRangeException();
            }
            set 
            {
                int start, length;
                if (GetWord(document.TextArray, 0, index, out start, 
                                                         out length)) 
                {
                    // 用字符串“value”替换位于 start/length 处的 
                    // 字:
                    if (length == value.Length) 
                    {
                        Array.Copy(value.ToCharArray(), 0, 
                                 document.TextArray, start, length);
                    }
                    else 
                    {
                        char[] newText = 
                            new char[document.TextArray.Length + 
                                           value.Length - length];
                        Array.Copy(document.TextArray, 0, newText, 
                                                        0, start);
                        Array.Copy(value.ToCharArray(), 0, newText, 
                                             start, value.Length);
                        Array.Copy(document.TextArray, start + length,
                                   newText, start + value.Length,
                                  document.TextArray.Length - start
                                                            - length);
                        document.TextArray = newText;
                    }
                }                    
                else
                    throw new IndexOutOfRangeException();
            }
        }

        // 获取包含文档中字的计数:
        public int Count 
        {
            get 
            { 
                int count = 0, start = 0, length = 0;
                while (GetWord(document.TextArray, start + length, 0, 
                                              out start, out length))
                    ++count;
                return count; 
            }
        }
    }

    // 以下类型允许以类似字符数组的方式查看文档
    // :
    public class CharacterCollection
    {
        readonly Document document;  // 包含文档

        internal CharacterCollection(Document d)
        {
          document = d; 
        }

        // 获取和设置包含文档中的字符的索引器:
        public char this[int index] 
        {
            get 
            { 
                return document.TextArray[index]; 
            }
            set 
            { 
                document.TextArray[index] = value; 
            }
        }

        // 获取包含文档中字符的计数:
        public int Count 
        {
            get 
            { 
                return document.TextArray.Length; 
            }
        }
    }

    // 由于字段的类型具有索引器， 
    // 因此这些字段显示为“索引属性”:
    public WordCollection Words;
    public CharacterCollection Characters;

    private char[] TextArray;  // 文档的文本。 

    public Document(string initialText)
    {
        TextArray = initialText.ToCharArray();
        Words = new WordCollection(this);
        Characters = new CharacterCollection(this);
    }

    public string Text 
    {
        get 
        { 
           return new string(TextArray); 
        }
    }
}

class Test
{
    static void Main()
    {
        Document d = new Document(
           "peter piper picked a peck of pickled peppers. How many pickled peppers did peter piper pick?"
        );

        // 将单词“peter”更改为“penelope”:
        for (int i = 0; i < d.Words.Count; ++i) 
        {
            if (d.Words[i] == "peter") 
                d.Words[i] = "penelope";
        }

        // 将字符“p”更改为“P”
        for (int i = 0; i < d.Characters.Count; ++i) 
        {
            if (d.Characters[i] == 'p')
                d.Characters[i] = 'P';
        }
        
        Console.WriteLine(d.Text);
    }
}

