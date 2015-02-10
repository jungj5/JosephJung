using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Test_ItemDatabase : MonoBehaviour {
	public List<Item> items = new List<Item> ();

	void Start() {
		items.Add(new Item("Amulet of Prayers", 0, "An amulet enchanted by prayers", 2, 0, Item.ItemType.Weapon));
		items.Add(new Item("White Shirt", 1, "A shirt that is white", 0, 0, Item.ItemType.Weapon));

	}

}
