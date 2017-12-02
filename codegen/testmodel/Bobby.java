import annotation.accessors.*;
import annotation.json.*;
import annotation.qualifiers.*;
import annotation.*;
import package1.*;

@JsonEntity
@Header(comments="Bobby is a JsonEntity reflecting XXX")
public class Bobby {
    int prout;

    @GetterSetter
    String foo;

    @Getter
    Bobby54 otherBobby;

    @Const
    @Pointer
    @GetterSetter
    Bobby54 BobbyConstPtr;
}
