-- UMass Lowell
-- Organization of Programming Languages (OPL)
-- by Phong Vo - Spring 2019
-- Assignment 1
-- reference link: https://rosettacode.org/wiki/Permutations#Ada

with Ada.Text_IO;  use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

with Ada.Command_Line, Generic_Perm;

-- add a package Generic_Perm
generic
	N: positive;
package Generic_Perm is
	subtype Element is Positive range 1 .. N;
	type Permutation is array(Element) of Element;
 
	procedure Set_To_First(P: out Permutation; Is_Last: out Boolean);
	procedure Go_To_Next(P: in out Permutation; Is_Last: out Boolean); 
end Generic_Perm;


-- implementation
package body Generic_Perm is
	procedure Set_To_First(P: out Permutation; Is_Last: out Boolean) is
	begin
		for I in P'Range loop
		P (I) := I;
		end loop;
		Is_Last := P'Length = 1; 
		-- if P has a single element, the fist permutation is the last one
	end Set_To_First;
 
	procedure Go_To_Next(P: in out Permutation; Is_Last: out Boolean) is
 
		procedure Swap (A, B : in out Integer) is
			C : Integer := A;
		begin
			A := B;
			B := C;
		end Swap;
 
		I, J, K : Element;      
	begin
		-- find longest tail decreasing sequence
		-- after the loop, this sequence is I+1 .. n,
		-- and the ith element will be exchanged later
		-- with some element of the tail
		Is_Last := True;
		I := N - 1;
		loop
			if P (I) < P (I+1)
				then
					Is_Last := False;
				exit;
			end if;
	 
			-- next instruction will raise an exception if I = 1, so
			-- exit now (this is the last permutation)
			exit when I = 1;
			I := I - 1;
		end loop;

		-- if all the elements of the permutation are in
		-- decreasing order, this is the last one
		if Is_Last then
			return;
		end if;

		-- sort the tail, i.e. reverse it, since it is in decreasing order
		J := I + 1;
		K := N;
		while J < K loop
			Swap (P (J), P (K));
			J := J + 1;
			K := K - 1;
		end loop;
 
		-- find lowest element in the tail greater than the ith element
		J := N;
		while P (J) > P (I) loop
			J := J - 1;
		end loop;
		J := J + 1;
 
		-- exchange them
		-- this will give the next permutation in lexicographic order,
		-- since every element from ith to the last is minimum
		Swap (P (I), P (J));
	end Go_To_Next;
end Generic_Perm;

-- procedure
with Ada.Text_IO, Ada.Command_Line, Generic_Perm;
 
procedure Print_Perms is
		package CML renames Ada.Command_Line;
		package TIO renames Ada.Text_IO;
	begin
		declare
			package Perms is new Generic_Perm(Positive'Value(CML.Argument(1)));
			P : Perms.Permutation;
			Done : Boolean := False;

			procedure Print(P: Perms.Permutation) is
			begin
				for I in P'Range loop
					TIO.Put (Perms.Element'Image (P (I)));
				end loop;
				TIO.New_Line;
			end Print;         
		begin
			Perms.Set_To_First(P, Done);
			loop
				Print(P);
				exit when Done;
				Perms.Go_To_Next(P, Done);
			end loop;
		end;
	exception
		when Constraint_Error 
			=> TIO.Put_Line ("*** Error: enter one numerical argument n with n >= 1");
end Print_Perms;


