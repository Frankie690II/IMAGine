// Working list operations

list check={1,2,3};
print(check);
len=length(check);
print("Length of list is "+len);
print("-------------------");

list li={4,5,6,"string"};
foreach(var:li){
	print(var);
}

print("-------------------");
list li2={-4.5,-4.6,"other string"};
push(li,li2);
print(li);

lenli=length(li);
print("Length of list is "+lenli);
print("-------------------");

// -------------------------------------------


print(check);
print("-------------------");
pop(li);
print(li);
print("-------------------");
//pop(5);
insert(li,-5.5,3);
remove(li,1);
el=get(li,2);
print(el);
