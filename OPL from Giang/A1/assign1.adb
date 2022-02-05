with Ada.Text_IO;  use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
procedure Assign1 is
   generic
      type Integers is range <>;
   package Combinations is
      type Combination is array (Positive range <>) of Integers;
      procedure First (X : in out Combination);
      procedure Next (X : in out Combination); 
      procedure Put (X : Combination);
   end Combinations;
 
   package body Combinations is
      procedure First (X : in out Combination) is
      begin
         X (1) := Integers'First;
         for I in 2..X'Last loop
            X (I) := X (I - 1) + 1;
         end loop;
      end First;
      procedure Next (X : in out Combination) is
      begin
         for I in reverse X'Range loop
            if X (I) < Integers'Val (Integers'Pos (Integers'Last) - X'Last + I) then
               X (I) := X (I) + 1;
               for J in I + 1..X'Last loop
                  X (J) := X (J - 1) + 1;
               end loop;
               return;
            end if;
         end loop;
         raise Constraint_Error;
      end Next;
      procedure Put (X : Combination) is
      begin
         for I in X'Range loop
            Put (Integers'Image (X (I)));
         end loop;
      end Put;
   end Combinations;
 
   N : Integer;
   K : Integer;
begin
   Put("Enter an integer for N: ");
   Get(N);
   Put("Enter an integer for K: ");
   Get(K);
   declare
      subtype K_Range is Integer range 1 .. K;
      package Combination_K is new Combinations (K_Range);
      use Combination_K;
      X : Combination (1..N);
   begin
      First (X);
      loop
            Put (X); New_Line;
            Next (X);
      end loop;
   end;
exception
   when Constraint_Error =>
      null;
end Assign1;