// Working flows
list check={1,2,3};
print(check);
len=length(check);
print("length is "+len);
print("-------------------");

list li={1,2,3,"string"};

foreach(var:li){
	print(var);
}

print("-------------------");
list li2={-4.5,-5.6,"other"};
push(li,li2);
push(li, 5);
print(li);
lenli=length(li);
print("length is "+lenli);
print("-------------------");

// -------------------------------------------

//pop(li);
remove(li,5 );
print("-------------------");
print(li);
lenli=length(li);
print("length is "+lenli);
print("-------------------");
pop(check);
print("-------------------");
print(check);
pop(5);
