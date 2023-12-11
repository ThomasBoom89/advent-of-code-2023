Imports System.IO

Module Program
    Sub Main(args As String())
        Console.WriteLine("Hello World!")
        ' Store the line in this String.
        Dim filePath As String =
                "/home/thomas/projects/github.com/advent-of-code-2023/src/lesson2/aoc-lesson2/aoc-lesson2/data-lesson2.txt"
'        lessonA(filePath)
        lessonB(filePath)
    End Sub

    Private Sub lessonA(filePath As String)

        Dim sum = 0
        For Each line As String In File.ReadLines(filePath)
            Dim gameSplit = line.Split(":")
'            Console.WriteLine(gameSplit(0))
            Dim game = gameSplit(0).Split()
            Dim gameId = game(1)
            Dim rounds = gameSplit(1).Split(";")
            if (Not CheckRound(rounds))
                Continue For
            End If

            sum = sum + Int32.Parse(gameId)
        Next line
        Console.WriteLine(sum)
    End Sub

    Private Sub lessonB(filePath As String)

        Dim sum = 0
        For Each line As String In File.ReadLines(filePath)
            Dim gameSplit = line.Split(":")
'            Console.WriteLine(gameSplit(0))
            Dim game = gameSplit(0).Split()
            Dim gameId = game(1)
            Dim rounds = gameSplit(1).Split(";")
            sum = sum + CalculateRounds(rounds)
        Next line
        Console.WriteLine(sum)
    End Sub

    Private Function CalculateRounds(rounds As String()) As Integer
        Dim dict = new Dictionary (Of String,Int32)
        For Each round in rounds
            CalculateRound(dict, round)
        Next
        Dim sum = 1
        For Each value In dict.Values
            sum = sum*value
        Next

        return sum
    End Function

    Private Function CalculateRound(dict As Dictionary(Of String,Integer), round As String)
        Dim roundParts = round.Split(",")
        For Each roundPart In roundParts
            Dim parts = roundPart.TrimStart().Split()
            if Not dict.ContainsKey(parts(1))
                dict.Add(parts(1), Int32.Parse(parts(0)))
                Continue For
            End If
            if dict.Item(parts(1)) <= Int32.Parse(parts(0))
                dict.Remove(parts(1))
                dict.Add(parts(1), Int32.Parse(parts(0)))
            End If
        Next
    End Function

    Private Function CheckRound(rounds As String()) As Boolean
        For Each round In rounds
            Dim roundParts = round.Split(",")
            If (Not CheckParts(roundParts))
                return False
            End If
        Next round

        return True
    End Function

    Private Function CheckParts(roundParts As String()) As Boolean
'        only 12 red cubes, 13 green cubes, and 14 blue cubes
        For Each roundPart In roundParts
            Dim parts = roundPart.TrimStart().Split()
            Dim compare = 12
            Select Case parts(1)
                Case "green"
                    compare = 13
                Case "blue"
                    compare = 14
            End Select
            If compare < Int32.Parse(parts(0))
                return False
            End If
        Next roundPart
        return True
    End Function
End Module
