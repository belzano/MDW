import annotation.accessors.*;
import annotation.json.*;
import package1.*;

@JsonEntity
public class Bobby {
    int prout;

    @GetterSetter
    String foo;

    @Getter
    Bobby54 otherBobby;

    //@Const
    //@Pointer
    @GetterSetter
    Bobby54 BobbyConstPtr;
}
