Module Module1

    Class RJKClass
        Private m_id As Integer

        Public Sub New(ByVal id As Integer)
            m_id = id
        End Sub

        Public Sub IAm()
            Console.WriteLine(m_id)
        End Sub

        Public Property ID() As Integer
            Get
                Return m_id
            End Get
            Set(ByVal value As Integer)
                m_id = value
            End Set
        End Property

    End Class


    Sub Main()
        Dim c1 As New RJKClass(1)
        Dim c2 As New RJKClass(2)

        c1.IAm()
        c2.IAm()

    End Sub

End Module
