package animation;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;

import application.Service;

/**
 * Use to get the animation if you know the name of the skill
 */
public class ConnectorSkillAnim {
  ArrayList<AnimationSkill> anims;
  
  /**
   * constructor should initialize all available names
   */
  public ConnectorSkillAnim() {
    anims = new ArrayList<AnimationSkill>();
    anims.add(new AnimationFire("fire"));
    anims.add(new AnimationWater("water"));
    anims.add(new AnimationEarth("earth"));
    anims.add(new AnimationWind("wind"));
  }
  
  /**
   * use if animation and skill has the same name and both are implement INamedObject
   * @param name
   * @return new AnimationSkill object
   */
  public AnimationSkill getAnimation(String name) {
    return (AnimationSkill) Service.getINamedObject(anims, name);
  }

  /**
   * use if you have the name if animation class(field className)
   * @param className
   * @param skillName
   * @return
   * @throws InstantiationException
   * @throws IllegalAccessException
   * @throws ClassNotFoundException
   * @throws NoSuchMethodException
   * @throws SecurityException
   * @throws IllegalArgumentException
   * @throws InvocationTargetException
   */
  public AnimationOneToOneFly getOneToOneFly(String className, String skillName)
      throws InstantiationException, IllegalAccessException, ClassNotFoundException,
      NoSuchMethodException, SecurityException, IllegalArgumentException,
      InvocationTargetException {
    Object[] args = new Object[] {skillName};
    @SuppressWarnings("rawtypes")
    Constructor constructor = Class.forName("animation." + className).getConstructor(String.class);
    return (AnimationOneToOneFly) (constructor.newInstance(args));
  }

}







