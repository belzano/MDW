package annotation;

import model.EntityModel;
import model.EntityModelContext;

public abstract class EntityModelWriter {

    public String writeEntityContentDefinition(EntityModel entityModel) {
        return "";
    }

    public String writeEntityContentDeclaration(EntityModel entityModel) {
        return "";
    }

    public String writeContextDeclaration(EntityModelContext entityModelContext) {
        return "";
    }

    public String writeContextDefinition(EntityModelContext entityModelContext) {
        return "";
    }

}
