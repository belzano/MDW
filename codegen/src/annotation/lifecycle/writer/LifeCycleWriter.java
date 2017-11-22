package annotation.lifecycle.writer;

import annotation.EntityModelWriter;
import model.EntityModel;
import model.EntityModelContext;

public class LifeCycleWriter extends EntityModelWriter{

    public String writeEntityContentDefinition(EntityModel entityModel) {
        return "Class();";
    }

    public String writeEntityContentDeclaration(EntityModel entityModel) {
        return "Class::Class() { }";
    }

    public String writeContextDeclaration(EntityModelContext entityModelContext) {
        return "";
    }

    public String writeContextDefinition(EntityModelContext entityModelContext) {
        return "";
    }

}
