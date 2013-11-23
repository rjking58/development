using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Linq.Expressions;

namespace Chapter3LambdaExpressions
{
    class Program
    {
        static void Main(string[] args)
        {
            // Create the expression tree.    
            Expression<Func<String, bool>> MyLambdaExpression =       MyString => MyString.Length > 3;    
            // Obtain the expression tree elements.    
            // Contains the list of parameters.    
            ParameterExpression Parameters =     (ParameterExpression)MyLambdaExpression.Parameters[0];    
            // Contains the evaluation.    
            BinaryExpression TheEvaluation =       (BinaryExpression)MyLambdaExpression.Body;    
            // Contains the left side of the evaluation.    
            MemberExpression LeftSide =       (MemberExpression)TheEvaluation.Left;    
            // Contains the right side of the evaluation.    
            ConstantExpression RightSide =       (ConstantExpression)TheEvaluation.Right;   
            
            // Output the elements of the expression tree.    
            Console.WriteLine("The tree contains:\r\nParameters: " 
                                +   Parameters.ToString() 
                                +   "\r\nEvaluation: " +   TheEvaluation.ToString() 
                                +   "\r\nLeft Side: " +   LeftSide.ToString() 
                                +   "\r\nNodeType: " + TheEvaluation.NodeType
                                +   "\r\nRight Side: " +       RightSide.ToString());
            

        }
        
        
    }
}
