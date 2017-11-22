import annotation.accessors.*;
import annotation.json.*;
//import annotation.json.decorator.*;
import annotation.*;

//@CodeGenerator(decorator = annotation.json.decorator.JsonEntity.class)
@JsonEntity
class Bobby {
    int prout;

    @Setter
    String foo;
}