local t = {
  quickbar_1 = string.format("[item=%s],[item=%s],[item=%s],[item=%s],[item=%s],[item=%s],[item=%s],[item=%s],[item=%s],[item=%s]",
	"wood","coal","stone","iron-ore","copper-ore","copper-cable","iron-gear-wheel","electronic-circuit","advanced-circuit","processing-unit"),
  quickbar_2 = string.format("[item=%s],[item=%s],[item=%s],[item=%s],[item=%s],[item=%s],[item=%s],[item=%s],[item=%s],[item=%s]",
	"iron-plate","copper-plate","steel-plate","plastic-bar","automation-science-pack","logistic-science-pack","chemical-science-pack","boiler","steam-engine","offshore-pump"),
  quickbar_3 = string.format("[item=%s],[item=%s],[item=%s],[item=%s],[item=%s],[item=%s],[item=%s],[item=%s],[item=%s],[item=%s]",
	"transport-belt","underground-belt","splitter","burner-inserter","inserter","long-handed-inserter","fast-inserter","small-electric-pole","pipe","pipe-to-ground"),
  quickbar_4 = string.format("[item=%s],[item=%s],[item=%s],[item=%s],[item=%s],[item=%s],[item=%s],[item=%s],[item=%s],[item=%s]",
	"stone-furnace","steel-furnace","assembling-machine-1","assembling-machine-2","lab","burner-mining-drill","electric-mining-drill","pumpjack","oil-refinery","chemical-plant"),
  none = ""
}

data:extend(
{
  {
    type = "string-setting",
    name = "DunRaider-quickbar-1",
    setting_type = "runtime-global",
    default_value = t.quickbar_1,
    allow_blank = true,
    order = "q1",
  },
  {
    type = "string-setting",
    name = "DunRaider-quickbar-2",
    setting_type = "runtime-global",
    default_value = t.quickbar_2,
    allow_blank = true,
    order = "q2",
  },
  {
    type = "string-setting",
    name = "DunRaider-quickbar-3",
    setting_type = "runtime-global",
    default_value = t.quickbar_3,
    allow_blank = true,
    order = "q3",
  },
  {
    type = "string-setting",
    name = "DunRaider-quickbar-4",
    setting_type = "runtime-global",
    default_value = t.quickbar_4,
    allow_blank = true,
    order = "q4",
  },
  {
    type = "string-setting",
    name = "DunRaider-quickbar-5",
    setting_type = "runtime-global",
    default_value = t.none,
    allow_blank = true,
    order = "q5",
  },
  {
    type = "string-setting",
    name = "DunRaider-quickbar-6",
    setting_type = "runtime-global",
    default_value = t.none,
    allow_blank = true,
    order = "q6",
  },
  {
    type = "string-setting",
    name = "DunRaider-quickbar-7",
    setting_type = "runtime-global",
    default_value = t.none,
    allow_blank = true,
    order = "q7",
  },
  {
    type = "string-setting",
    name = "DunRaider-quickbar-8",
    setting_type = "runtime-global",
    default_value = t.none,
    allow_blank = true,
    order = "q8",
  },
  {
    type = "string-setting",
    name = "DunRaider-quickbar-9",
    setting_type = "runtime-global",
    default_value = t.none,
    allow_blank = true,
    order = "q9",
  },
  {
    type = "string-setting",
    name = "DunRaider-quickbar-10",
    setting_type = "runtime-global",
    default_value = t.none,
    allow_blank = true,
    order = "q91",
  },
})